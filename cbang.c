
#include "cbang.h"

#include "cbnull.h"
#include "cbstring.h"
#include "cbinteger.h"

static list *class_list;

int method_name_equals(const void *methodp, va_list args);
int class_name_equals(const void *class, va_list args);

void cbang_init() {
	class_list = create_list();

	push_back(class_list, cbnull_init());
	push_back(class_list, cbstring_init());
	push_back(class_list, cbinteger_init());
}

var cbang_message_send(var o, string message, ...) {
	method *the_method;
	va_list argp;

	the_method = get_first_occurrence(o->class->methods, method_name_equals, message);

	if (!the_method) {
		fprintf(stderr, "Object of class %s does not respond to message \"%s\"\n", o->class->name, message);
		exit(EXIT_FAILURE);
	}

	va_start(argp, message);

	return the_method->function(o, argp);
}

int method_name_equals(const void *methodp, va_list args) {
	string name;
	method *the_method = (method *)methodp;

	name = malloc(sizeof(char) * strlen(the_method->name));
	assert(name);

	vsprintf(name, "%s", args);

	if (strcmp(the_method->name, name) == 0) {
		free(name);
		return 1;
	}

	free(name);
	return 0;
}

var cbang_constructor(string class_name, ...) {
	class *the_class;
	va_list argp;
	var retval;

	the_class = get_first_occurrence(class_list, class_name_equals, class_name);

	if (!the_class) {
		fprintf(stderr, "Cannot construct object of class \"%s\"\n", class_name);
		exit(EXIT_FAILURE);
	}

	va_start(argp, class_name);

	retval = the_class->constructor(argp);

	va_end(argp);

	return retval;
}

int class_name_equals(const void *classp, va_list args) {
	string name;
	class *the_class = (class *)classp;

	name = malloc(sizeof(char) * strlen(the_class->name));
	assert(name);

	vsprintf(name, "%s", args);

	if (strcmp(the_class->name, name) == 0) {
		free(name);
		return 1;
	}

	free(name);
	return 0;
}

void cbang_release(var v) {
	if (v->data) {
		free(v->data);
	}
	
	free(v);
}

class *mclass(string name, cpointer constructor) {
	class *the_class = malloc(sizeof(class));
	assert(the_class);

	list *methods = create_list();
	the_class->methods = methods;

	the_class->name = name;

	the_class->constructor = constructor;

	return the_class;
}

method *mmethod(string name, fpointer function) {
	method *the_method = malloc(sizeof(method));
	assert(the_method);

	the_method->name = name;

	the_method->function = function;

	return the_method;
}

var mvar(class *class) {
	var the_var = malloc(sizeof(obj));
	assert(the_var);
	the_var->class = class;

	return the_var;
}

string mstring(string s) {
	string the_string = malloc(sizeof(char) * (strlen(s) + 1));
	assert(the_string);
	strcpy(the_string, s);
	return the_string;
}