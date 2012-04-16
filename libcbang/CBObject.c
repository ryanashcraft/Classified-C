
#include "CBang.h"
#include "CBObject.h"

Class ObjectClass = NULL;

static void *init(void *v, va_list *args);

static void *release(void *v, va_list *args);
static void *print(void *v, va_list *args);

void object_class_init() {
	method m;

	ObjectClass = message(ClassClass, "init", "Object", NULL);

	m = mmethod("init", &init);
	push_back(ObjectClass->methods, m);

	m = mmethod("release", &release);
	push_back(ObjectClass->instance_methods, m);
	m = mmethod("print", &print);
	push_back(ObjectClass->instance_methods, m);
}

void *init(void *v, va_list *args) {
	Object o = calloc(1, sizeof(struct _CBObject));
	assert(o);

	o->class = ObjectClass;
	o->methods = ObjectClass->instance_methods;
	o->parent = NULL;

	return o;
}

void *release(void *v, va_list *args) {
	Object o = (Object)v;
	free(o);
	return o;
}

void *print(void *v, va_list *args) {
	fprintf(stderr, "Object");
	return NULL;
}

