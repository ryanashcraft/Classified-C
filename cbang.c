
#include "cbang.h"

#include "cbobject.h"
#include "cbnull.h"
#include "cbstring.h"
#include "cbinteger.h"

static list *class_list;

int method_name_equals(const void *methodp, va_list args);
int class_name_equals(const void *class, va_list args);

void cbang_init() {
	class_list = create_list();

	push_back(class_list, cbobject_init());
	push_back(class_list, cbnull_init());
	push_back(class_list, cbstring_init());
	push_back(class_list, cbinteger_init());
}

var message(var v, string message, ...) {
	method the_method;
	va_list argp;

	the_method = get_first_occurrence(v->type->methods, method_name_equals, message);

	while (!the_method && v->parent != NULL) {
		v = v->parent;
		the_method = get_first_occurrence(v->type->methods, method_name_equals, message);
	}

	if (!the_method) {
		fprintf(stderr, "Object of type %s does not respond to message \"%s\"\n", v->type->name, message);
		exit(EXIT_FAILURE);
	}

	va_start(argp, message);

	return the_method->function(v, argp);
}

int method_name_equals(const void *methodp, va_list args) {
	string name;
	method the_method = (method)methodp;

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

var construct(string class_name, ...) {
	class the_class;
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
	class the_class = (class)classp;

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

void release(var v) {
	if (v->data) {
		free(v->data);
	}

	free(v);
}

class mclass(string name, string parent_class_name, cpointer constructor) {
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

	return the_class;
}

method mmethod(string name, fpointer function) {
	method the_method = malloc(sizeof(struct _method));
	assert(the_method);

	the_method->name = name;

	the_method->function = function;

	return the_method;
}

var mvar(class type) {
	var the_var = malloc(sizeof(struct _obj));
	assert(the_var);
	the_var->type = type;

	the_var->parent = NULL;
	/* set data to NULL so that it won't try to free later if never set */
	the_var->data = NULL;

	var v = the_var;
	while (v->type->parent != NULL) {
		v->parent = mvar(v->type->parent);
		v = v->parent;
	}

	return the_var;
}

string mstring(string s) {
	string the_string = malloc(sizeof(char) * (strlen(s) + 1));
	assert(the_string);
	strcpy(the_string, s);
	return the_string;
}