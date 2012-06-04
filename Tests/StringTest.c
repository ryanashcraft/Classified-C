
#include "../libclassc/Classified-C.h"
#include "Test.h"
#include "StringTest.h"

IMPLEMENTATION(StringTestClass);

PROTOTYPE(new);
PROTOTYPE(testNewWithCString);
PROTOTYPE(testNewWithFormatCString);

void string_test_class_init() {
	StringTestClass = msg(ClassClass, "new", "StringTest", TestClass);

	REGISTER_CLASS_METHOD(StringTestClass, "new", new);

	REGISTER_METHOD(StringTestClass, "testNewWithCString", testNewWithCString);
	REGISTER_METHOD(StringTestClass, "testNewWithFormatCString", testNewWithFormatCString);
}

DEFINE(new) {
	NEW(StringTestClass, struct _StringTest);

	msg_cast(TestClass, self, "init");

	String testCase = msg(StringClass, "newWithCString", "testNewWithCString");
	msg(self, "addTestCase", testCase);
	msg(testCase, "release");

	testCase = msg(StringClass, "newWithCString", "testNewWithFormatCString");
	msg(self, "addTestCase", testCase);
	msg(testCase, "release");

	return self;
}

DEFINE(testNewWithCString) {
	CONTEXT(StringTest);

	String foo = msg(StringClass, "newWithCString", "foo");
	Boolean isEqual = msg(foo, "equals", "foo");
	msg(foo, "release");

	return msg_cast(TestClass, self, "assertTrue", isEqual);
}

DEFINE(testNewWithFormatCString) {
	CONTEXT(StringTest);

	String foo = msg(StringClass, "newWithFormatCString", "%s %d", "foo", 5);
	Boolean isEqual = msg(foo, "equals", "foo 5");
	msg(foo, "release");

	return msg_cast(TestClass, self, "assertTrue", isEqual);
}
