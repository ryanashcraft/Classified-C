
#define CLASS Integer
#define SUPER Object

#include "Classified-C.h"

proto(newWithInt);
proto(initWithInt);
proto(equals);
proto(greaterThan);
proto(lessThan);
proto(description);
proto(increment);

defclass
	constructor(newWithInt);
	
	instance(initWithInt);
	instance(equals);
	instance(greaterThan);
	instance(lessThan);
	instance(description);
	instance(increment);
end

defcon(newWithInt)
	initWithInt(self, args);

	return self;
end

def(initWithInt)
	self->value = nextArg(int);

	return self;
end

def(equals)
	Integer other = nextArg(Integer);

	if (self->value == other->value) {
		return YES;
	}

	return NO;
end


def(greaterThan)
	Integer other = nextArg(Integer);

	if (self->value > other->value) {
		return YES;
	}

	return NO;
end

def(lessThan)
	Integer other = nextArg(Integer);

	if (self->value < other->value) {
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

int to_int(Integer i) {
	return i->value;
}
