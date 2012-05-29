
#include "../libcbang/CBang.h"
#include "FooClass.h"

int main(int argc, char **argv) {
	cbinit();
	foo_class_init();

	Object o = msg(ObjectClass, "new");
	String description = msg(o, "description");
	msg(SystemOut, "println", "%@", description);
	msg(o, "release");
	msg(description, "release");

	Null n = msg(NullClass, "new");
	description = msg(n, "description");
	msg(SystemOut, "println", "%@", description);
	msg(description, "release");
	msg(n, "release");

	String ohhai = msg(StringClass, "newWithCString", "oh hai");

	String st = msg(StringClass, "newWithFormatCString", "test %@ %d %f", ohhai, 5, 4.0);
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
	description = msg(mys, "description");
	msg(SystemOut, "println", "%@", description);
	msg(description, "release");
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
