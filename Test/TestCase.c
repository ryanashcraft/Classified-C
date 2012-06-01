
#include "../libclassc/Classified-C.h"
#include "TestCase.h"

IMPLEMENTATION(TestCaseClass);

PROTOTYPE(new);
PROTOTYPE(init);

void test_case_class_init() {
	TestCaseClass = msg(ClassClass, "new", "TestCase", ObjectClass);

	REGISTER_CLASS_METHOD(TestCaseClass, "new", new);

	REGISTER_METHOD(TestCaseClass, "init", init);
}

DEFINE(new) {
	NEW(TestCaseClass, struct _TestCase);

	init(self, args);

	return self;
}

DEFINE(init) {
	CONTEXT(TestCase);

	self->function = NEXT_ARG(test_case_func);

	return self;
}

DEFINE(run) {
	CONTEXT(TestCase);

	int result = self->function();

	msg(SystemOut, "println", "%d", result);

	return self;
}
