
#include "CBang.h"

Class IteratorClass = NULL;

static void *newWithArray(void *v, va_list *args);

static void *initWithArray(void *v, va_list *args);
static void *dealloc(void *v, va_list *args);
static void *next(void *v, va_list *args);

void iterator_class_init() {
	IteratorClass = msg(ClassClass, "new", "Iterator", ObjectClass);

	push_back(IteratorClass->static_methods, mmethod("newWithArray", &newWithArray));
	
	push_back(IteratorClass->instance_methods, mmethod("initWithObjects", &initWithArray));
	push_back(IteratorClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(IteratorClass->instance_methods, mmethod("next", &next));
}

void *newWithArray(void *v, va_list *args) {
	Iterator o = cballoc(sizeof(struct _CBIterator));
	initWithArray(o, args);
	((Object)o)->root = IteratorClass;
	return o;
}

void *initWithArray(void *v, va_list *args) {
	Iterator o = (Iterator)v;
	msg_cast(ObjectClass, o, "init");

	o->elements = va_arg(*args, Array);
	msg(o->elements, "retain");

	o->nextPointer = 0;

	return o;
}

void *dealloc(void *v, va_list *args) {
	Iterator o = (Iterator)v;

	msg(o->elements, "release");

	return msg_cast(ObjectClass, o, "dealloc");
}

void *next(void *v, va_list *args) {
	Iterator o = (Iterator)v;

	Integer length = msg(o->elements, "length");
	if (o->nextPointer >= length->value) {
		msg(length, "release");
		return NULL;
	}
	msg(length, "release");

	return msg(o->elements, "get", o->nextPointer++);
}
