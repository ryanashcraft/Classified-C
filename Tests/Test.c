
#define TYPE Test
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
	static(new);

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

	return msg_cast(ObjectClass, self, "dealloc");
end

def(description)
	return msg(StringClass, "newWithCString", ((Object)self)->root->name);
end

def(addTestCase)
	String testCase = NEXT_ARG(String);
	msg(self->testCases, "pushBack", testCase);

	return self;
end

def(run)
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
end

def(assertEquals)
	if (msg(NEXT_ARG(Object), "equals", NEXT_ARG(Object))) {
		return TestCaseResultSuccess;
	}

	return (void *)TestCaseResultFailure;
end

def(assertTrue)
	if (msg(BooleanClass, "isYes", NEXT_ARG(size_t))) {
		return TestCaseResultSuccess;
	}

	return (void *)TestCaseResultFailure;
end
