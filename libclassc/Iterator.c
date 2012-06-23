
#include "Classified-C.h"

#define TYPE Iterator
#define SUPER ObjectClass

proto(newWithArray)
proto(newWithLinkedList)
proto(initWithArray)
proto(initWithLinkedList)
proto(dealloc)
proto(next)

defclass
	registerStatic("newWithArray", newWithArray);
	registerStatic("newWithLinkedList", newWithLinkedList);
	
	register("initWithObjects", initWithArray);
	register("initWithLinkedList", initWithLinkedList);
	register("dealloc", dealloc);
	register("next", next);
end

defcon(newWithArray)
	initWithArray(self, args);

	return self;
end

defcon(newWithLinkedList)
	initWithLinkedList(self, args);

	return self;
end

def(initWithArray)
	self->elements = NEXT_ARG(Object);
	msg(self->elements, "retain");
	self->nextPointer = 0;

	return self;
end

def(initWithLinkedList)
	self->elements = NEXT_ARG(Object);
	msg(self->elements, "retain");
	self->nextPointer = 0;

	return self;
end

def(dealloc)
	msg(self->elements, "release");

	return msg_cast(ObjectClass, self, "dealloc");
end

def(next)
	Integer length = msg(self->elements, "length");
	if (self->nextPointer >= length->value) {
		msg(length, "release");
		return NULL;
	}
	
	msg(length, "release");

	return msg(self->elements, "get", self->nextPointer++);
end
