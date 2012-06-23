
#include "Classified-C.h"

#define TYPE Integer
#define SUPER ObjectClass

proto(newWithInt)
proto(initWithInt)
proto(equals)
proto(description)
proto(increment)

defclass
	registerStatic("newWithInt", newWithInt);
	
	register("initWithInt", initWithInt);
	register("equals", equals);
	register("description", description);
	register("increment", increment);
end

defcon(newWithInt)
	initWithInt(self, args);

	return self;
end

def(initWithInt)
	self->value = NEXT_ARG(size_t);

	return self;
end

def(equals)
	size_t other = NEXT_ARG(size_t);

	if (self->value == other) {
		return YES;
	}

	return NO;
end

def(description)
	return msg(StringClass, "newWithFormatCString", "%d", self->value);
end

def(increment)
	self->value++;

	return self;
end
