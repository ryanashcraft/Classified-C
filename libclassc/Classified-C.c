/**
  Classified-C.c

  This file contains functions and data structures used for managing
  the set of CBang classes and implementing message passing.

  @author Ryan Ashcraft
 */

#include "Classified-C.h"
#include <execinfo.h>

Object systemOut = NULL;
Thread mainThread = NULL;

static Object cbmessage(Object o, Class c, cstring message, va_list *args);
static Object cbmessageclass(Class c, cstring message, va_list *args);
static void print_bt();

/**
  Initialize the class list and the standard classes
 */
void cc_init() {
	// Initialize and register standard classes to the class list
	ClassInit();
	ObjectInit();
	IteratorInit();
	StringInit();
	MutableStringInit();
	LinkedListInit();
	ThreadInit();
	NullInit();
	ArrayInit();
	IntegerInit();
	BooleanInit();
	StackInit();
	FileInit();
	ScannerInit();
	PrinterInit();

	systemOut = msg(PrinterClass, "newWithFile", msg(FileClass, "newWithFile", stderr));
	mainThread = msg(ThreadClass, "new");
}

void cc_end() {
	msg(ThreadClass, "joinAllThreads");
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
void *msg(void *v, cstring message, ...) {
	va_list argp;
	Object o = (Object)v;

	if (o->retaincount <= 0) {
		// Only message allowed when retain count is zero is dealloc
		assert(strcmp(message, "dealloc") == 0);
	}

	Class c = o->root;

	// Instantiate the variable argument list for the method's parameters
	va_start(argp, message);

	if (c == ClassClass) {
		return cbmessageclass((Class)o, message, &argp);
	}

	// Call the method's function pointer with the object and a reference
	// to the variable argument list
	return cbmessage(o, c, message, &argp);
}

void *msgCast(Class c, void *v, cstring message, ...) {
	va_list argp;
	Object o = (Object)v;

	// Instantiate the variable argument list for the method's parameters
	va_start(argp, message);

	// Call the method's function pointer with the object and a reference
	// to the variable argument list
	return cbmessage(o, c, message, &argp);
}

Object cbmessageclass(Class c, cstring message, va_list *argp) {
	Class startC = c;
	method *m;

	int message_length = strlen(message);

	// Try to get the method from the object's type
	m = ht_get(c->static_methods, message, message_length);

	// While the method isn't found and there is a parent, then look in the
	// parent's type
	while (!m && c->parent_class != NULL) {
		c = c->parent_class;
		m = ht_get(c->static_methods, message, message_length);
	}

	// If the method is never found, then error and exit out
	if (!m) {
		fprintf(stderr, "Class of type %s does not respond to message \"%s\"\n", startC->name, message);
		print_bt();
		exit(EXIT_FAILURE);
	}

	return m->function(c, argp);
}

Object cbmessage(Object o, Class c, cstring message, va_list *argp) {
	Class startC = c;
	method *m;

	int message_length = strlen(message);

	// Try to get the method from the object's type
	m = ht_get(c->instance_methods, message, message_length);

	// While the method isn't found and there is a parent, then look in the
	// parent's type
	while (!m && c->parent_class != NULL) {
		c = c->parent_class;
		m = ht_get(c->instance_methods, message, message_length);
	}

	// If the method is never found, then error and exit out
	if (!m) {
		fprintf(stderr, "Object of type %s does not respond to message \"%s\"\n", startC->name, message);
		print_bt();
		exit(EXIT_FAILURE);
	}

	return m->function(o, argp);
}

void *msgWithMessage(void *messagep) {
	struct _message *message = (struct _message *)messagep;
	Object target = message->target;
	cstring selector = message->selector;
	va_list *argp = message->argp;
	free(message);
	return cbmessage(target, target->root, selector, argp);
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

void *cc_alloc(size_t size) {
	void *v = calloc(1, size);
	assert(v);
	((Object)v)->retaincount = 1;

	return v;
}

void msg_release(void *v) {
	msg(v, "release");	
}

/**
  Helper function for creating a new method.

  @param name     the name of the method
  @param function the function pointer

  @return a malloc'ed method struct with its members defined
 */
method *mmethod(cstring name, fpointer function) {
	method *m = malloc(sizeof(struct _method));
	assert(m);

	m->name = mstring(name);
	m->function = function;

	return m;
}

void dmethod(method *m) {
	free(m->name);
	free(m);
}

void ht_insert_method(hashtable **table, void *key, size_t key_size, void *value, size_t value_size) {
	ht_insert(table, key, key_size, value, value_size);
	dmethod(value);
}

/**
  Helper function creating a new malloc'ed string.

  @param s the cstring to copy from

  @return a malloc'ed version of the string
 */
cstring mstring(cstring s) {
	cstring the_string = malloc(strlen(s) + 1);
	assert(the_string);
	the_string = strncpy(the_string, s, strlen(s) + 1);
	return the_string;
}
