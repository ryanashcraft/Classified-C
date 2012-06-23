
#define CLASS Foo
#define SUPER String

#include "../libclassc/Classified-C.h"
#include "FooClass.h"

proto(new);
proto(init);
proto(dealloc);
proto(description);

defclass
	static(new);

	instance(init);
	instance(dealloc);
	instance(description);
end

defcon(new)
	init(self, args);

	return self;
end

def(init)
	int value = NEXT_ARG(int);
	msg_cast(StringClass, self, "initWithCString", NEXT_ARG(cstring));
	self->value = value;

	return self;
end

def(dealloc)
	return msg_cast(StringClass, self, "dealloc");
end

def(description)
	String superDescription = msg_cast(StringClass, self, "description");
	String formattedDescription = msg(StringClass, "newWithFormatCString", "%d %@", self->value, superDescription);
	msg(superDescription, "release");

	return formattedDescription;
end
