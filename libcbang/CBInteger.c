
#include "CBang.h"
#include "CBInteger.h"

Class IntegerClass = NULL;

static void *initWithInt(void *v, va_list *args);

static void *release(void *v, va_list *args);

void integer_class_init() {
	method m;

	IntegerClass = message(ClassClass, "init", "IntegerClass", ObjectClass);

	m = mmethod("initWithInt", &initWithInt);
	push_back(IntegerClass->methods, m);

	m = mmethod("release", &release);
	push_back(IntegerClass->instance_methods, m);
}

void *initWithInt(void *v, va_list *args) {
	Integer o;

	o = calloc(1, sizeof(struct _CBInteger));
	assert(o);

	o->class = IntegerClass;
	o->methods = IntegerClass->instance_methods;
	o->parent = message(ObjectClass, "init");

	o->value = va_arg(*args, int);

	return o;
}

void *release(void *v, va_list *args) {
	Integer o = (Integer)v;
	message(o->parent, "release");
	free(o);
	return o;
}