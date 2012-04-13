/**
  CBang.c

  This file contains functions and data structures used for managing
  the set of CBang classes and implementing message passing.

  @author Ryan Ashcraft
 */

#include "CBang.h"

static list *class_list;

void *construct_parent(void *v, class type, va_list *argp);

int method_name_equals(const void *methodp, va_list *args);
int class_name_equals(const void *class, va_list *args);

/**
  Initialize the class list and the standard classes.
 */
void cbang_init() {
	if (class_list) {
		return;
	}

	class_list = create_list();

	push_back(class_list, cbobject_init());
	push_back(class_list, cbnull_init());
	push_back(class_list, cbstring_init());
	push_back(class_list, cbinteger_init());
	push_back(class_list, cbstack_init());
	push_back(class_list, cbfile_init());
	push_back(class_list, cbscanner_init());
}

/**
  Add a class to the class list (if it isn't already added).

  @param c the class to add
 */
void add_class(class c) {
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
	class type = ((CBObject)v)->type;
	method the_method;
	va_list argp;

	the_method = get_first_occurrence(type->methods, method_name_equals, message);

	while (!the_method && type->parent != NULL) {
		v = type->super(v);
		type = type->parent;
		the_method = get_first_occurrence(type->methods, method_name_equals, message);
	}

	if (!the_method) {
		fprintf(stderr, "Object of type %s does not respond to message \"%s\"\n", type->name, message);
		exit(EXIT_FAILURE);
	}

	va_start(argp, message);

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

  @param class_name the name of the class that the object is to be constructed by
  @param ...        variable arguments that will be passed as parameters to the
                    object's constructor

  @param the constructed object
 */
void *construct(string class_name, ...) {
	class the_class;
	va_list argp;
	void *v = NULL;
	void *p = NULL; /* make sure to set to NULL */

	the_class = get_first_occurrence(class_list, class_name_equals, class_name);

	if (!the_class) {
		fprintf(stderr, "Cannot construct object of class \"%s\"\n", class_name);
		exit(EXIT_FAILURE);	
	}

	va_start(argp, class_name);

	v = the_class->constructor(v, &p, &argp);

	if (the_class->parent != NULL) {
		construct_parent(p, the_class->parent, &argp);
	}

	va_end(argp);

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
	void *p = NULL;

	v = type->constructor(v, &p, argp);

	if (type->parent != NULL) {
		construct_parent(p, type->parent, argp);
	}

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
	if (!v) {
		return;
	}
	
	class type = ((CBObject)v)->type;

	if (type->destructor) {
		type->destructor(v);
	}

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