
#include "Classified-C.h"

static Boolean yesInstance = NULL;
static Boolean noInstance = NULL;

IMPLEMENTATION(BooleanClass);

PROTOTYPE(newWithInt);
PROTOTYPE(yes);
PROTOTYPE(no);

void boolean_class_init() {
	BooleanClass = msg(ClassClass, "new", "Integer", IntegerClass);

	REGISTER_CLASS_METHOD(BooleanClass, "newWithInt", newWithInt);
	REGISTER_CLASS_METHOD(BooleanClass, "yes", yes);
	REGISTER_CLASS_METHOD(BooleanClass, "no", no);

	yesInstance = msg(BooleanClass, "newWithInt", 1);
	noInstance = msg(BooleanClass, "newWithInt", 0);
}

DEFINE(newWithInt) {
	NEW(BooleanClass, struct _Boolean);

	msg(self, "initWithInt", args);

	return self;
}

DEFINE(yes) {
	return yesInstance;
}

DEFINE(no) {
	return noInstance;
}
