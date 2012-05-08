/**
  CBang.c

  This file contains functions and data structures used for managing
  the set of CBang classes and implementing message passing.

  @author Ryan Ashcraft
 */

#include "CBang.h"
#include <execinfo.h>

var SystemOut = NULL;

static void *cbmessage(Object o, Class c, string message, va_list *args);
static void print_bt();
static int method_name_equals(const void *methodp, va_list *args);

/**
  Initialize the class list and the standard classes
 */
void cbinit() {
	// Initialize and register standard classes to the class list
	class_class_init();
	object_class_init();
	null_class_init();
	string_class_init();
	// integer_class_init();
	// stack_class_init();
	file_class_init();
	// scanner_class_init();
	printer_class_init();

	SystemOut = msg_class(PrinterClass, "newWithFile", msg_class(FileClass, "newWithFile", stderr));
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
void *msg(void *v, string message, ...) {
	va_list argp;
	Object o = (Object)v;
	Class c = o->root;

	// Instantiate the variable argument list for the method's parameters
	va_start(argp, message);

	// Call the method's function pointer with the object and a reference
	// to the variable argument list
	return cbmessage(o, c, message, &argp);
}

void *msg_cast(Class c, void *v, string message, ...) {
	va_list argp;
	Object o = (Object)v;

	// Instantiate the variable argument list for the method's parameters
	va_start(argp, message);

	// Call the method's function pointer with the object and a reference
	// to the variable argument list
	return cbmessage(o, c, message, &argp);
}

void *msg_class(Class c, string message, ...) {
	va_list argp;
	Class startC = c;
	method the_method;

	// Try to get the method from the object's type
	the_method = get_first_occurrence(c->static_methods, method_name_equals, message);

	// While the method isn't found and there is a parent, then look in the
	// parent's type
	while (!the_method && c->parent_class != NULL) {
		c = c->parent_class;
		the_method = get_first_occurrence(c->static_methods, method_name_equals, message);
	}

	// If the method is never found, then error and exit out
	if (!the_method) {
		fprintf(stderr, "Class %s does not respond to message \"%s\"\n", startC->name, message);
		print_bt();
		exit(EXIT_FAILURE);
	}

	// Instantiate the variable argument list for the method's parameters
	va_start(argp, message);

	return the_method->function((Object)c, &argp);
}

void *cbmessage(Object o, Class c, string message, va_list *argp) {
	Class startC = c;
	method the_method;

	// Try to get the method from the object's type
	the_method = get_first_occurrence(c->instance_methods, method_name_equals, message);

	// While the method isn't found and there is a parent, then look in the
	// parent's type
	while (!the_method && c->parent_class != NULL) {
		c = c->parent_class;
		the_method = get_first_occurrence(c->instance_methods, method_name_equals, message);
	}

	// If the method is never found, then error and exit out
	if (!the_method) {
		fprintf(stderr, "Object of type %s does not respond to message \"%s\"\n", startC->name, message);
		print_bt();
		exit(EXIT_FAILURE);
	}

	return the_method->function(o, argp);
}

void print_bt() {
	void *array[10];
	size_t size;
	char **strings;
	size_t i;
     
	size = backtrace(array, 10);
	strings = backtrace_symbols(array, size);

	printf("Obtained %zd stack frames.\n", size);

	for (i = 0; i < size; i++)
		printf ("%s\n", strings[i]);

	free(strings);
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

void *cballoc(size_t size) {
	void *v = calloc(1, size);
	assert(v);
	((Object)v)->retaincount = 1;

	return v;
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

	the_method->name = mstring(name);
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