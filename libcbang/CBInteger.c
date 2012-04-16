
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

	i->parent = message(ObjectClass, "init");

	return i;
}

void *release(void *v, va_list *args) {
	Integer i = (Integer)v;
	message(i->parent, "release");
	free_list(i->methods, &free);
	free(i);
	return i;
}