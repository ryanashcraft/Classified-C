
#define CLASS Foo
#define SUPER String

#include "../libclassc/Classified-C.h"
#include "FooClass.h"

proto(new);
proto(init);
proto(description);
proto(print);

defclass
	static(new);

	instance(init);
	instance(description);
	instance(print);
end

defcon(new)
	init(self, args);

	return self;
end

def(init)
	int value = NEXT_ARG(int);
	msgSuper("initWithCString", NEXT_ARG(cstring));
	self->value = value;

	return self;
end

def(description)
	String superDescription = msgSuper("description");
	String formattedDescription = msg(StringClass, "newWithFormatCString", "%d %@", self->value, superDescription);
	msg(superDescription, "release");

	return formattedDescription;
end

def(print)
	msg(systemOut, "println", "I'M MAD AS HELL AND I'M NOT GOING TO TAKE IT ANYMORE! %@", self);

	return self;
end
