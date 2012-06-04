
#include "../libclassc/Classified-C.h"
#include "Test.h"

IMPLEMENTATION(TestClass);

PROTOTYPE(new);
PROTOTYPE(init);
PROTOTYPE(dealloc);
PROTOTYPE(description);
PROTOTYPE(addTestCase);
PROTOTYPE(run);
PROTOTYPE(assertEquals);
PROTOTYPE(assertTrue);

void test_class_init() {
	TestClass = msg(ClassClass, "new", "Test", ObjectClass);

	REGISTER_CLASS_METHOD(TestClass, "new", new);

	REGISTER_METHOD(TestClass, "init", init);
	REGISTER_METHOD(TestClass, "dealloc", dealloc);
	REGISTER_METHOD(TestClass, "description", description);
	REGISTER_METHOD(TestClass, "addTestCase", addTestCase);
	REGISTER_METHOD(TestClass, "run", run);
	REGISTER_METHOD(TestClass, "assertEquals", assertEquals);
	REGISTER_METHOD(TestClass, "assertTrue", assertTrue);
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

	String testCase = NEXT_ARG(String);
	msg(self->testCases, "pushBack", testCase);

	return self;
}

DEFINE(run) {
	CONTEXT(Test);

	Integer totalTestCases = msg(self->testCases, "length");
	Integer successCount = msg(IntegerClass, "newWithInt", 0);

	msg(SystemOut, "println", "%@:", self);

	String testCase = NULL;
	Iterator iterator = msg(IteratorClass, "newWithLinkedList", self->testCases);
	while ( (testCase = msg(iterator, "next")) ) {
		msg(SystemOut, "print", "\t%@: ", testCase);

		TestCaseResult result = (TestCaseResult)msg(self, msg(testCase, "cString"));

		if (result == TestCaseResultSuccess) {
			msg(SystemOut, "println", "%s", "success");
			msg(successCount, "increment");
		} else {
			msg(SystemOut, "println", "%s", "failure");
		}
	}
	msg(iterator, "release");

	msg(SystemOut, "println", "%@ successes / %@ total", successCount, totalTestCases);
	msg(successCount, "release");
	msg(totalTestCases, "release");

	return self;
}

DEFINE(assertEquals) {
	if (msg(NEXT_ARG(Object), "equals", NEXT_ARG(Object))) {
		return TestCaseResultSuccess;
	}

	return (void *)TestCaseResultFailure;
}

DEFINE(assertTrue) {
	if (msg(BooleanClass, "isYes", NEXT_ARG(size_t))) {
		return TestCaseResultSuccess;
	}

	return (void *)TestCaseResultFailure;
}
