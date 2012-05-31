
#include "Classified-C.h"

IMPLEMENTATION(IteratorClass);

PROTOTYPE(newWithArray);
PROTOTYPE(initWithArray);
PROTOTYPE(dealloc);
PROTOTYPE(next);

void iterator_class_init() {
	IteratorClass = msg(ClassClass, "new", "Iterator", ObjectClass);

	REGISTER_CLASS_METHOD(IteratorClass, "newWithArray", newWithArray);
	
	REGISTER_METHOD(IteratorClass, "initWithObjects", initWithArray);
	REGISTER_METHOD(IteratorClass, "dealloc", dealloc);
	REGISTER_METHOD(IteratorClass, "next", next);
}

DEFINE(newWithArray) {
	NEW(IteratorClass, struct _Iterator);

	initWithArray(self, args);

	return self;
}

DEFINE(initWithArray) {
	CONTEXT(Iterator);

	self->elements = NEXT_ARG(Array);
	msg(self->elements, "retain");
	self->nextPointer = 0;

	return self;
}

DEFINE(dealloc) {
	CONTEXT(Iterator);

	msg(self->elements, "release");

	return msg_cast(ObjectClass, self, "dealloc");
}

DEFINE(next) {
	CONTEXT(Iterator);

	Integer length = msg(self->elements, "length");
	if (self->nextPointer >= length->value) {
		msg(length, "release");
		return NULL;
	}
	msg(length, "release");

	return msg(self->elements, "get", self->nextPointer++);
}
