
#define CLASS Integer
#define SUPER Object

#include "Classified-C.h"

proto(newWithInt);
proto(initWithInt);
proto(equals);
proto(description);
proto(increment);

defclass
	static(newWithInt);
	
	instance(initWithInt);
	instance(equals);
	instance(description);
	instance(increment);
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
	return msg(msg(StringClass, "newWithFormatCString", "%d", self->value), "autoRelease");
end

def(increment)
	self->value++;

	return self;
end
