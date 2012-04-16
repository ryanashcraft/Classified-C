
#include "CBang.h"
#include "CBInteger.h"

Class IntegerClass = NULL;

static void *initWithInt(void *v, va_list *args);
static void *super(void *v);

void integer_class_init() {
	method m;

	IntegerClass = message(ClassClass, "init", "IntegerClass", ObjectClass, &super);

	m = mmethod(mstring("initWithInt"), &initWithInt);
	push_back(IntegerClass->methods, m);
}

void *initWithInt(void *v, va_list *args) {
	Integer i;

	i = malloc(sizeof(struct _CBInteger));
	assert(i);

	i->class = IntegerClass;
	i->methods = create_list();
	i->value = va_arg(*args, int);

	message(ObjectClass, "initWithPointer", &(i->parent));

	return i;
}

void *super(void *v) {
	Integer i = (Integer)v;
	return &(i->parent);
}
