
#include "Classified-C.h"

static Boolean yesInstance = NULL;
static Boolean noInstance = NULL;

IMPLEMENTATION(BooleanClass);

PROTOTYPE(newWithInt);
PROTOTYPE(yes);
PROTOTYPE(no);
PROTOTYPE(isYes);

void boolean_class_init() {
	BooleanClass = msg(ClassClass, "new", "Integer", IntegerClass);

	REGISTER_CLASS_METHOD(BooleanClass, "newWithInt", newWithInt);
	REGISTER_CLASS_METHOD(BooleanClass, "yes", yes);
	REGISTER_CLASS_METHOD(BooleanClass, "no", no);
	REGISTER_CLASS_METHOD(BooleanClass, "isYes", isYes);

	yesInstance = msg(BooleanClass, "newWithInt", YES);
	noInstance = msg(BooleanClass, "newWithInt", NO);
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

DEFINE(isYes) {
	if (NEXT_ARG(size_t) == (size_t)NO) {
		return NO;
	}

	return YES;
}
