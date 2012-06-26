
#define CLASS Foo
#define SUPER String

#include "../libclassc/Classified-C.h"
#include "FooClass.h"

proto(new);
proto(init);
proto(description);
proto(catAndPrint);

defclass
	static(new);

	instance(init);
	instance(description);
	instance(catAndPrint);
end

defcon(new)
	init(self, args);

	return self;
end

def(init)
	int value = nextArg(int);
	msgSuper("initWithCString", nextArg(cstring));
	self->value = value;

	return self;
end

def(description)
	String superDescription = msgSuper("description");
	String formattedDescription = msg(StringClass, "newWithFormatCString", "%d %@", self->value, superDescription);

	return msg(formattedDescription, "autoRelease");
end

def(catAndPrint)
	LinkedList userData = nextArg(LinkedList);
	String cat = msg(userData, "getFront");
	msg(systemOut, "println", "%@ %@", cat, self);

	return self;
end
