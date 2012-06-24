
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

def(catAndPrint)
	LinkedList userData = NEXT_ARG(LinkedList);
	String cat = msg(userData, "getFront");
	msg(systemOut, "println", "%@ %@", cat, self);

	return self;
end
