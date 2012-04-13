/**
  CBang.c

  This file contains functions and data structures used for managing
  the set of CBang classes and implementing message passing.

  @author Ryan Ashcraft
 */

#include "CBang.h"

static list *class_list = NULL;

void *construct_parent(void *v, class type, va_list *argp);

int method_name_equals(const void *methodp, va_list *args);
int class_name_equals(const void *class, va_list *args);

/**
  Initialize the class list and the standard classes
 */
void cbang_init() {
	// Return the class list if it is already instantiated
	if (class_list) {
		return;
	}

	// Instantiate the class list. 
	class_list = create_list();

	// Initialize and register standard classes to the class list
	push_back(class_list, cbobject_init());
	push_back(class_list, cbnull_init());
	push_back(class_list, cbstring_init());
	push_back(class_list, cbinteger_init());
	push_back(class_list, cbstack_init());
	push_back(class_list, cbfile_init());
	push_back(class_list, cbscanner_init());
}

/**
  Add a class to the class list (if it isn't already added)

  @param c the class to add
 */
void add_class(class c) {
	// If the class isn't currently in the class list, then add it. 
	if (find_occurrence(class_list, c, NULL) == 0) {
		push_back(class_list, c);
	}
}

/**
  Send a message to an object.

  Find the method that corresponds to the message provided. If the method
  isn't found in the object v's method set, then recursively loop up the
  class heirarchy of the object until there is a class that responds to the
  message.

  If no method is ever found in any of the classes of the object, then
  report the error and exit. If a method is found, then pass in the variable
  argument list into that method's function pointer along with the pointer
  to the object v.

  @param v       the pointer to an object for where to send the message to
  @param message the message to send to the object
  @param ...     variable arguments that will be passed as parameters to
                 the object's method

  @return the object returned from the function call
 */
void *message(void *v, string message, ...) {
	method the_method;
	va_list argp;
	class type = ((CBObject)v)->type;

	// Try to get the method from the object's type
	the_method = get_first_occurrence(type->methods, method_name_equals, message);

	// While the method isn't found and there is a parent, then look in the
	// parent's type
	while (!the_method && type->parent != NULL) {
		v = type->super(v);
		type = type->parent;
		the_method = get_first_occurrence(type->methods, method_name_equals, message);
	}

	// If the method is never found, then error and exit out
	if (!the_method) {
		fprintf(stderr, "Object of type %s does not respond to message \"%s\"\n", type->name, message);
		exit(EXIT_FAILURE);
	}

	// Instantiate the variable argument list for the method's parameters
	va_start(argp, message);

	// Call the method's function pointer with the object and a reference
	// to the variable argument list
	return the_method->function(v, &argp);
}

/**
  Compare a method's name to a string.

  @param methodp the pointer to a method
  @param args    variable argument list, which is expected to have a char
                 pointer at the argument's address

  @return 1 if the method's name equals the string from the variable
          arguments list, else return 0
 */
int method_name_equals(const void *methodp, va_list *args) {
	string name = va_arg(*args, string);
	method the_method = (method)methodp;
	if (strcmp(the_method->name, name) == 0) {
		return 1;
	}
	return 0;
}

/**
  Construct an object.

  If the class name argument doesn't match any classes in the class list, then
  report the error and exit.

  Upon finding the class that correspodns to the given class name, then use the
  constructor of that class to allocate and construct the object. If the object's
  class has any parent classes, then continue to construct the object with that
  parent class' constructor (except this time, the pointer that is passed into
  the constructor is pointing to an inner "parent" member of the original object).

  @param class_name the name of the class that the object is to be constructed by
  @param ...        variable arguments that will be passed as parameters to the
                    object's constructor

  @param the constructed object
 */
void *construct(string class_name, ...) {
	class the_class;
	va_list argp;

	// Pointer for the object that will be returned
	// Needs to be set to NULL on declaration or bad things might happen
	void *v = NULL;
	// Pointer that might be set to a pointer of the object's parent struct
	void *p = NULL;

	// Try to get the class with name class_name
	the_class = get_first_occurrence(class_list, class_name_equals, class_name);

	// If no class is found, then error and exit out
	if (!the_class) {
		fprintf(stderr, "Cannot construct object of class \"%s\"\n", class_name);
		exit(EXIT_FAILURE);	
	}

	// Instantiate the variable argument list for the constructor's parameters
	va_start(argp, class_name);

	// Call the class's constructor with a pointer for the object, a pointer for
	// the object's parent struct (which is a member of the object's struct),
	// and the variable argument list
	v = the_class->constructor(v, &p, &argp);

	// If there is a parent, then construct the parent with the pointer to the
	// object's parent struct and the remaining variable arguments
	if (the_class->parent != NULL) {
		construct_parent(p, the_class->parent, &argp);
	}

	// End the variable argument list
	va_end(argp);

	// Return the original object
	return v;
}

/**
  Continue the construction of an object by calling the constructors of the
  parents of the object.

  @param v    the object
  @param type the class for the object that has the constructor function
  @param argp variable argument list, which has the parameters for the
              constructor function

  @return the object v
 */
void *construct_parent(void *v, class type, va_list *argp) {
	// Pointer that might be set to a pointer of the object's parent struct
	void *p = NULL;

	// Call the constructor on the object with a pointer that can be set to the
	// object's parent struct
	v = type->constructor(v, &p, argp);

	// If there is a parent, then construct the parent with the pointer to the
	// object's parent struct and the remaining variable arguments
	if (type->parent != NULL) {
		// Recursive call with terminating condition when the object passed in
		// doesn't have a parent
		construct_parent(p, type->parent, argp);
	}

	// Return the object
	return v;
}

/**
  Compare a class's name to a string.

  @param classp the pointer to a class
  @param args   variable argument list, which is expected to have a char
                pointer at the argument's address

  @return 1 if the class's name equals the string from the variable
          arguments list, else return 0
 */
int class_name_equals(const void *classp, va_list *args) {
	string name = va_arg(*args, string);
	class the_class = (class)classp;
	if (strcmp(the_class->name, name) == 0) {
		return 1;
	}
	return 0;
}

/**
  Destruct an object by calling its destructor and freeing the object.

  @param v the object to destruct
 */
void destruct(void *v) {
	// If the obejct is NULL, then return out
	if (!v) {
		return;
	}
	
	// The class of the object
	class type = ((CBObject)v)->type;

	// Call the destructor, if it is defined in the class, with the object
	// to free any internally allocated members of the object
	if (type->destructor) {
		type->destructor(v);
	}

	// Free the object
	free(v);
}

/**
  Helper function for creating a new class.

  @param name              the name of the class
  @param parent_class_name the name of the parent class
  @param constructor       the function pointer to the class constructor
  @param destructor        the function pointer to the class destructor
  @param super             the function pointer to the class super function

  @return a malloc'ed class struct with its members defined
 */
class mclass(string name, string parent_class_name, cpointer constructor, dpointer destructor, spointer super) {
	class parent_class = NULL;

	class the_class = malloc(sizeof(struct _class));
	assert(the_class);

	list *methods = create_list();
	the_class->methods = methods;

	the_class->name = name;

	if (!parent_class_name) {
		parent_class = get_first_occurrence(class_list, class_name_equals, "CBObject");
	} else {
		parent_class = get_first_occurrence(class_list, class_name_equals, parent_class_name);
	}
	the_class->parent = parent_class;

	the_class->constructor = constructor;
	the_class->destructor = destructor;
	the_class->super = super;

	return the_class;
}

/**
  Helper function for creating a new method.

  @param name     the name of the method
  @param function the function pointer

  @return a malloc'ed method struct with its members defined
 */
method mmethod(string name, fpointer function) {
	method the_method = malloc(sizeof(struct _method));
	assert(the_method);

	the_method->name = name;

	the_method->function = function;

	return the_method;
}

/**
  Helper function creating a new malloc'ed string.

  @param s the string to copy from

  @return a malloc'ed version of the string
 */
string mstring(string s) {
	string the_string = malloc(strlen(s) + 1);
	assert(the_string);
	strncpy(the_string, s, strlen(s) + 1);
	return the_string;
}