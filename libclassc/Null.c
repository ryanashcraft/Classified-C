
#include "Classified-C.h"

IMPLEMENTATION(NullClass);

PROTOTYPE(new);

void null_class_init() {
	NullClass = msg(ClassClass, "new", "Null", ObjectClass);

	REGISTER_CLASS_METHOD(NullClass, "new", new);
}

DEFINE(new) {
	NEW(NullClass, struct _Null);
	return self;
}
