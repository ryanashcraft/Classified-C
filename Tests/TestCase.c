
#include "../libclassc/Classified-C.h"
#include "TestCase.h"

IMPLEMENTATION(TestCaseClass);

PROTOTYPE(newWithNameAndFunction);
PROTOTYPE(initWithNameAndFunction);
PROTOTYPE(dealloc);
PROTOTYPE(description);
PROTOTYPE(run);

void test_case_class_init() {
	TestCaseClass = msg(ClassClass, "new", "TestCase", ObjectClass);

	REGISTER_CLASS_METHOD(TestCaseClass, "newWithNameAndFunction", newWithNameAndFunction);

	REGISTER_METHOD(TestCaseClass, "initWithNameAndFunction", initWithNameAndFunction);
	REGISTER_METHOD(TestCaseClass, "dealloc", dealloc);
	REGISTER_METHOD(TestCaseClass, "description", description);
	REGISTER_METHOD(TestCaseClass, "run", run);
}

DEFINE(newWithNameAndFunction) {
	NEW(TestCaseClass, struct _TestCase);

	initWithNameAndFunction(self, args);

	return self;
}

DEFINE(initWithNameAndFunction) {
	CONTEXT(TestCase);

	self->name = mstring(NEXT_ARG(cstring));
	self->function = NEXT_ARG(test_case_func);

	return self;
}

DEFINE(dealloc) {
	CONTEXT(TestCase);

	free(self->name);

	return msg_cast(ObjectClass, self, "dealloc");
}

DEFINE(description) {
	CONTEXT(TestCase);

	return msg(StringClass, "newWithFormatCString", "%s", self->name);
}

DEFINE(run) {
	CONTEXT(TestCase);

	msg(SystemOut, "print", "\t%@: ", self);

	int result = self->function();
	if (result == TestCaseResultSuccess) {
		msg(SystemOut, "println", "%s", "success");
		return YES;
	}

	msg(SystemOut, "println", "%s", "failure");
	return NO;
}
