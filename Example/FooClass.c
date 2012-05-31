
#include "../libclassc/Classified-C.h"
#include "FooClass.h"

IMPLEMENTATION(FooClass);

PROTOTYPE(new);
PROTOTYPE(init);
PROTOTYPE(dealloc);
PROTOTYPE(description);

void foo_class_init() {
	FooClass = msg(ClassClass, "new", "Foo", StringClass);

	REGISTER_CLASS_METHOD(FooClass, "new", new);

	REGISTER_METHOD(FooClass, "init", init);
	REGISTER_METHOD(FooClass, "dealloc", dealloc);
	REGISTER_METHOD(FooClass, "description", description);
}

DEFINE(new) {
	NEW(FooClass, struct _Foo);

	init(self, args);

	return self;
}

DEFINE(init) {
	CONTEXT(Foo);

	int value = NEXT_ARG(int);
	msg_cast(StringClass, self, "initWithCString", NEXT_ARG(cstring));
	self->value = value;

	return self;
}

DEFINE(dealloc) {
	CONTEXT(Foo);

	return msg_cast(StringClass, self, "dealloc");
}

DEFINE(description) {
	CONTEXT(Foo);

	String superDescription = msg_cast(StringClass, self, "description");
	String formattedDescription = msg(StringClass, "newWithFormatCString", "%d %@", self->value, superDescription);
	msg(superDescription, "release");

	return formattedDescription;
}
