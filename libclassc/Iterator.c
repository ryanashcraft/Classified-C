
#define CLASS Iterator
#define SUPER Object

#include "Classified-C.h"

proto(newWithArray);
proto(newWithLinkedList);
proto(initWithArray);
proto(initWithLinkedList);
proto(dealloc);
proto(next);

defclass {
	constructor(newWithArray);
	constructor(newWithLinkedList);
	
	instance(initWithArray);
	instance(initWithLinkedList);
	instance(dealloc);
	instance(next);
} end

defcon(newWithArray) {
	initWithArray(self, args);

	return self;
} end

defcon(newWithLinkedList) {
	initWithLinkedList(self, args);

	return self;
} end

def(initWithArray) {
	self->elements = nextArg(Object);
	msg(self->elements, "retain");
	self->nextPointer = 0;

	return self;
} end

def(initWithLinkedList) {
	self->elements = nextArg(Object);
	msg(self->elements, "retain");
	self->nextPointer = 0;

	return self;
} end

def(dealloc) {
	msg(self->elements, "release");

	return msgSuper("dealloc");
} end

def(next) {
	Integer length = msg(self->elements, "length");
	if (self->nextPointer >= length->value) {
		msg(length, "release");
		return NULL;
	}
	
	msg(length, "release");

	return msg(self->elements, "get", self->nextPointer++);
} end
