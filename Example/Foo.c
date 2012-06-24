
#include "../libclassc/Classified-C.h"
#include "FooClass.h"

int main(int argc, char **argv) {
	cc_init();
	FooInit();

	String s1 = msg(StringClass, "newWithCString", "1");
	String s2 = msg(StringClass, "newWithCString", "2");
	Integer i3 = msg(IntegerClass, "newWithInt", 3);
	Array arr = msg(ArrayClass, "newWithObjects", s1, s2, i3, NULL);
	msg(systemOut, "printEach", " ", arr);
	msg(arr, "performOnEach", "release");
	msg(arr, "release");
	msg(systemOut, "println", "");

	Object o = msg(ObjectClass, "new");
	msg(systemOut, "println", "%@", o);
	msg(o, "release");

	Null n = msg(NullClass, "new");
	msg(systemOut, "println", "%@", n);
	msg(n, "release");

	String ohhai = msg(StringClass, "newWithCString", "oh hai");

	String st = msg(StringClass, "newWithFormatCString", "test %d %f %@", 5, 4.0, ohhai);
	msg(systemOut, "println", "%@", st);
	msg(st, "release");

	msg(ohhai, "release");

	File f = msg(FileClass, "newWithFilename", "../README.md");
	Scanner s = msg(ScannerClass, "newWithFile", f);
	Integer hasNext = msg(IntegerClass, "newWithInt", 1);
	while (msg(hasNext, "equals", YES)) {
		String token = msg(s, "next");
		msg(systemOut, "print", "%@ ", token);
		msg(token, "release");

		msg(hasNext, "release");
		hasNext = msg(s, "hasNext");
	}
	msg(hasNext, "release");
	msg(s, "release");
	msg(f, "release");
	msg(systemOut, "println", "");

	Foo mys = msg(FooClass, "new", 77, "Foo");
	msg(systemOut, "println", "%@", mys);
	msg(mys, "release");

	Stack stack = msg(StackClass, "new");
	msg(stack, "push", msg(StringClass, "newWithCString", "Ryan"));
	msg(stack, "push", msg(StringClass, "newWithCString", "Tanner"));
	msg(stack, "pop");
	String str = msg(stack, "peek");
	if (str) {
		msg(systemOut, "println", "%@", str);
	}
	stack = msg(stack, "release");

	Thread thread = msg(ThreadClass, "currentThread");
	msg(systemOut, "println", "Current Thread: %@", thread);

	Foo threadFoo = msg(FooClass, "new", 88, "threadFoo");
	String qwerty = msg(StringClass, "newWithCString", "qwerty");
	Thread secondThread = msg(ThreadClass, "newWithTargetAndSelector", threadFoo, "print", qwerty);
	msg(secondThread, "run");
	msg(qwerty, "release");
	msg(threadFoo, "release");

	cc_end();
}
