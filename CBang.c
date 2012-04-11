
#include "CBang.h"

#include "CBObject.h"
#include "CBNull.h"
#include "CBString.h"
#include "CBInteger.h"
#include "CBStack.h"

static list *class_list;

void *construct_parent(void *v, class type, va_list argp);

int method_name_equals(const void *methodp, va_list args);
int class_name_equals(const void *class, va_list args);

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
}

void add_class(class c) {
	if (find_occurrence(class_list, c, NULL) == 0) {
		push_back(class_list, c);
	}
}

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

	return the_method->function(v, argp);
}

int method_name_equals(const void *methodp, va_list args) {
	string name;
	method the_method = (method)methodp;

	name = malloc(sizeof(char) * (strlen(the_method->name) + 1));
	assert(name);

	vsnprintf(name, sizeof(char) * (strlen(the_method->name) + 1), "%s", args);

	if (strcmp(the_method->name, name) == 0) {
		free(name);
		return 1;
	}

	free(name);
	return 0;
}

void *construct(string class_name, ...) {
	class the_class;
	va_list argp;
	void *v = NULL;
	void *p = NULL; /* why do i have to set this to NULL? */

	the_class = get_first_occurrence(class_list, class_name_equals, class_name);

	if (!the_class) {
		fprintf(stderr, "Cannot construct object of class \"%s\"\n", class_name);
		exit(EXIT_FAILURE);	
	}

	va_start(argp, class_name);

	v = the_class->constructor(v, &p, argp);

	if (the_class->parent != NULL) {
		construct_parent(p, the_class->parent, argp);
	}

	va_end(argp);

	return v;
}

void *construct_parent(void *v, class type, va_list argp) {
	void *p = NULL;

	v = type->constructor(v, &p, argp);

	if (type->parent != NULL) {
		construct_parent(p, type->parent, argp);
	}

	return v;
}

int class_name_equals(const void *classp, va_list args) {
	string name;
	class the_class = (class)classp;

	name = malloc(sizeof(char) * (strlen(the_class->name) + 1));
	assert(name);

	vsnprintf(name, sizeof(char) * (strlen(the_class->name) + 1), "%s", args);

	if (strcmp(the_class->name, name) == 0) {
		free(name);
		return 1;
	}

	free(name);
	return 0;
}

void destruct(void *v) {
	class type = ((CBObject)v)->type;

	if (type->destructor) {
		type->destructor(v);
	}

	free(v);
}

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

method mmethod(string name, fpointer function) {
	method the_method = malloc(sizeof(struct _method));
	assert(the_method);

	the_method->name = name;

	the_method->function = function;

	return the_method;
}

string mstring(string s) {
	string the_string = malloc(strlen(s) + 1);
	assert(the_string);
	strlcpy(the_string, s, strlen(s) + 1);
	return the_string;
}