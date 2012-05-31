
#include "../libclassc/Classified-C.h"
#include "FooClass.h"

int main(int argc, char **argv) {
	cc_init();
	foo_class_init();

	String s1 = msg(StringClass, "newWithCString", "1");
	String s2 = msg(StringClass, "newWithCString", "2");
	Integer i3 = msg(IntegerClass, "newWithInt", 3);
	Array arr = msg(ArrayClass, "newWithObjects", s1, s2, i3, NULL);
	msg(SystemOut, "printEach", " ", arr);
	msg(arr, "performMethodOnEach", "release");
	msg(arr, "release");
	msg(SystemOut, "println", "");

	Object o = msg(ObjectClass, "new");
	msg(SystemOut, "println", "%@", o);
	msg(o, "release");

	Null n = msg(NullClass, "new");
	msg(SystemOut, "println", "%@", n);
	msg(n, "release");

	String ohhai = msg(StringClass, "newWithCString", "oh hai");

	String st = msg(StringClass, "newWithFormatCString", "test %d %f %@", 5, 4.0, ohhai);
	msg(SystemOut, "println", "%@", st);
	msg(st, "release");

	msg(ohhai, "release");

	File f = msg(FileClass, "newWithFilename", "../README.md");
	Scanner s = msg(ScannerClass, "newWithFile", f);
	Integer hasNext = msg(IntegerClass, "newWithInt", 1);
	while (msg(hasNext, "equals", YES)) {
		String token = msg(s, "next");
		msg(SystemOut, "print", "%@ ", token);
		msg(token, "release");

		msg(hasNext, "release");
		hasNext = msg(s, "has_next");
	}
	msg(hasNext, "release");
	msg(s, "release");
	msg(f, "release");
	msg(SystemOut, "println", "");

	Foo mys = msg(FooClass, "new", 77, "Foo");
	msg(SystemOut, "println", "%@", mys);
	msg(mys, "release");

	Stack stack = msg(StackClass, "new");
	msg(stack, "push", msg(StringClass, "newWithCString", "Ryan"));
	msg(stack, "push", msg(StringClass, "newWithCString", "Tanner"));
	msg(stack, "pop");
	String str = msg(stack, "peek");
	if (str) {
		msg(SystemOut, "println", "%@", str);
	}
	stack = msg(stack, "release");
}
