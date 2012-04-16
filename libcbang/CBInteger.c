
#include "CBang.h"
#include "CBInteger.h"

Class IntegerClass = NULL;

static void *initWithInt(void *v, va_list *args);
static void *super(void *v);

static void *release(void *v, va_list *args);

void integer_class_init() {
	method m;

	IntegerClass = message(ClassClass, "init", "IntegerClass", ObjectClass, &super);

	m = mmethod("initWithInt", &initWithInt);
	push_back(IntegerClass->methods, m);
}

void *initWithInt(void *v, va_list *args) {
	Integer i;
	method m;

	i = malloc(sizeof(struct _CBInteger));
	assert(i);

	i->class = IntegerClass;
	i->value = va_arg(*args, int);

	i->methods = create_list();
	m = mmethod("release", &release);

	message(ObjectClass, "initWithPointer", &(i->parent));

	return i;
}

void *super(void *v) {
	Integer i = (Integer)v;
	return &(i->parent);
}

void *release(void *v, va_list *args) {
	Integer i = (Integer)v;
	message(super(i), "release");
	free_list(i->methods, &free);
	free(i);
	return i;
}