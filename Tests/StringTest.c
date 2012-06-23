
#define CLASS StringTest
#define SUPER Test

#include "../libclassc/Classified-C.h"
#include "Test.h"
#include "StringTest.h"

proto(new);
proto(testNewWithCString);
proto(testNewWithFormatCString);

defclass
	static(new);

	instance(testNewWithCString);
	instance(testNewWithFormatCString);
end

defcon(new)
	msg_cast(TestClass, self, "init");

	String testCase = msg(StringClass, "newWithCString", "testNewWithCString");
	msg(self, "addTestCase", testCase);
	msg(testCase, "release");

	testCase = msg(StringClass, "newWithCString", "testNewWithFormatCString");
	msg(self, "addTestCase", testCase);
	msg(testCase, "release");

	return self;
end

def(testNewWithCString)
	String foo = msg(StringClass, "newWithCString", "foo");
	Boolean isEqual = msg(foo, "equals", "foo");
	msg(foo, "release");

	return msg_cast(TestClass, self, "assertTrue", isEqual);
end

def(testNewWithFormatCString)
	String foo = msg(StringClass, "newWithFormatCString", "%s %d", "foo", 5);
	Boolean isEqual = msg(foo, "equals", "foo 5");
	msg(foo, "release");

	return msg_cast(TestClass, self, "assertTrue", isEqual);
end
