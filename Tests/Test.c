
#define CLASS Test
#define SUPER Object

#include "../libclassc/Classified-C.h"
#include "Test.h"

proto(new);
proto(init);
proto(dealloc);
proto(description);
proto(addTestCase);
proto(run);
proto(assertEquals);
proto(assertTrue);

defclass
	constructor(new);

	instance(init);
	instance(dealloc);
	instance(description);
	instance(addTestCase);
	instance(run);
	instance(assertEquals);
	instance(assertTrue);
}

def(new)
	init(self, args);

	return self;
end

def(init)
	self->testCases = msg(LinkedListClass, "new");

	return self;
end

def(dealloc)
	msg(self->testCases, "release");

	return msgSuper("dealloc");
end

def(description)
	return msg(StringClass, "newWithCString", ((Object)self)->root->name);
end

def(addTestCase)
	String testCase = nextArg(String);
	msg(self->testCases, "pushBack", testCase);

	return self;
end

def(run)
	Integer totalTestCases = msg(self->testCases, "length");
	Integer successCount = msg(IntegerClass, "newWithInt", 0);

	msg(systemOut, "println", "%@:", self);

	String testCase = NULL;
	Iterator iterator = msg(IteratorClass, "newWithLinkedList", self->testCases);
	while ( (testCase = msg(iterator, "next")) ) {
		msg(systemOut, "print", "\t%@: ", testCase);

		TestCaseResult result = (TestCaseResult)msg(self, msg(testCase, "cString"));

		if (result == TestCaseResultSuccess) {
			msg(systemOut, "println", "%s", "success");
			msg(successCount, "increment");
		} else {
			msg(systemOut, "println", "%s", "failure");
		}
	}
	msg(iterator, "release");

	msg(systemOut, "println", "%@ successes / %@ total", successCount, totalTestCases);
	msg(successCount, "release");
	msg(totalTestCases, "release");

	return self;
end

def(assertEquals)
	if (msg(nextArg(Object), "equals", nextArg(Object))) {
		return TestCaseResultSuccess;
	}

	return (void *)TestCaseResultFailure;
end

def(assertTrue)
	if (msg(BooleanClass, "isYes", nextArg(size_t))) {
		return TestCaseResultSuccess;
	}

	return (void *)TestCaseResultFailure;
end
