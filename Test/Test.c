
#include "../libclassc/Classified-C.h"
#include "Test.h"
#include "TestCase.h"

IMPLEMENTATION(TestClass);

PROTOTYPE(new);
PROTOTYPE(init);
PROTOTYPE(dealloc);

void test_class_init() {
	test_case_class_init();

	TestClass = msg(ClassClass, "new", "Test", ObjectClass);

	REGISTER_CLASS_METHOD(TestClass, "new", new);

	REGISTER_METHOD(TestClass, "init", init);
	REGISTER_METHOD(TestClass, "dealloc", dealloc);
}

DEFINE(new) {
	NEW(TestClass, struct _Test);

	init(self, args);

	return self;
}

DEFINE(init) {
	CONTEXT(Test);

	self->testCases = msg(LinkedListClass, "new");

	return self;
}

DEFINE(dealloc) {
	CONTEXT(Test);

	return msg_cast(ObjectClass, self, "dealloc");
}

DEFINE(runTests) {
	CONTEXT(Test);

	msg(self->testCases, "runOnEach", "run");

	return self;
}
