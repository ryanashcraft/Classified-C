
#include "CBang.h"
#include "CBNull.h"

Class NullClass = NULL;

static void *init(void *v, va_list *args);

static void *release(void *v, va_list *args);

void null_class_init() {
	method m;

	NullClass = message(ClassClass, "init", "NullClass", ObjectClass);

	m = mmethod("init", &init);
	push_back(NullClass->methods, m);

	m = mmethod("release", &release);
	push_back(NullClass->instance_methods, m);
}

void *init(void *v, va_list *args) {
	Null o;

	o = calloc(1, sizeof(struct _CBNull));
	assert(o);

	o->class = NullClass;
	o->methods = NullClass->instance_methods;
	o->parent = message(ObjectClass, "init");

	return o;
}

void *release(void *v, va_list *args) {
	Null o = (Null)v;
	message(o->parent, "release");
	free(o);
	return o;
}
