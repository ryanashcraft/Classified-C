
#include "../libclassc/Classified-C.h"
#include "Test.h"
#include "TestCase.h"

IMPLEMENTATION(TestClass);

PROTOTYPE(new);
PROTOTYPE(init);
PROTOTYPE(dealloc);
PROTOTYPE(description);
PROTOTYPE(addTestCase);
PROTOTYPE(run);

void test_class_init() {
	test_case_class_init();

	TestClass = msg(ClassClass, "new", "Test", ObjectClass);

	REGISTER_CLASS_METHOD(TestClass, "new", new);

	REGISTER_METHOD(TestClass, "init", init);
	REGISTER_METHOD(TestClass, "dealloc", dealloc);
	REGISTER_METHOD(TestClass, "description", description);
	REGISTER_METHOD(TestClass, "addTestCase", addTestCase);
	REGISTER_METHOD(TestClass, "run", run);
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

	msg(self->testCases, "release");

	return msg_cast(ObjectClass, self, "dealloc");
}

DEFINE(description) {
	CONTEXT(Test);

	return msg(StringClass, "newWithCString", ((Object)self)->root->name);
}

DEFINE(addTestCase) {
	CONTEXT(Test);

	TestCase testCase = NEXT_ARG(TestCase);
	msg(self->testCases, "pushBack", testCase);

	return self;
}

DEFINE(run) {
	CONTEXT(Test);

	Integer totalTestCases = msg(self->testCases, "length");
	Integer successCount = msg(IntegerClass, "newWithInt", 0);

	msg(SystemOut, "println", "%@:", self, totalTestCases);

	TestCase testCase = NULL;
	Iterator iterator = msg(IteratorClass, "newWithLinkedList", self->testCases);
	while ( (testCase = msg(iterator, "next")) ) {
		boolean successful = msg(testCase, "run");
		if (successful == YES) {
			msg(successCount, "increment");
		}
	}
	msg(iterator, "release");

	msg(SystemOut, "println", "%@ successes / %@ total", successCount, totalTestCases);
	msg(successCount, "release");
	msg(totalTestCases, "release");

	return self;
}
