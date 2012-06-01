
#include "../libclassc/Classified-C.h"
#include "Test.h"
#include "TestCase.h"
#include "StringTest.h"

IMPLEMENTATION(StringTestClass);

PROTOTYPE(new);

int test_new_with_cstring();
int test_new_with_format_cstring();

void string_test_class_init() {
	StringTestClass = msg(ClassClass, "new", "StringTest", TestClass);

	REGISTER_CLASS_METHOD(StringTestClass, "new", new);
}

DEFINE(new) {
	NEW(StringTestClass, struct _StringTest);

	msg_cast(TestClass, self, "init");

	TestCase testCase = msg(TestCaseClass, "newWithNameAndFunction", "newWithCString", test_new_with_cstring);
	msg(self, "addTestCase", testCase);
	msg(testCase, "release");

	testCase = msg(TestCaseClass, "newWithNameAndFunction", "newWithFormatCString", test_new_with_format_cstring);
	msg(self, "addTestCase", testCase);
	msg(testCase, "release");

	return self;
}

int test_new_with_cstring() {
	String foo = msg(StringClass, "newWithCString", "foo");
	boolean isEqual = msg(foo, "equals", "foo");
	msg(foo, "release");

	return isEqual ? TestCaseResultSuccess : TestCaseResultFailure;
}

int test_new_with_format_cstring() {
	String foo = msg(StringClass, "newWithFormatCString", "%s %d", "foo", 5);
	boolean isEqual = msg(foo, "equals", "foo 5");
	msg(foo, "release");

	return isEqual ? TestCaseResultSuccess : TestCaseResultFailure;
}
