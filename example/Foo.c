
#include "../libcbang/CBang.h"
#include "FooClass.h"

int main(int argc, char **argv) {
	cbinit();
	foo_class_init();

	Object o = msg_class(ObjectClass, "new");
	msg(SystemOut, "println", "%@", msg(o, "description"));
	msg(o, "release");

	Null n = msg_class(NullClass, "new");
	msg(SystemOut, "println", "%@", msg(n, "description"));
	msg(n, "release");

	String ohhai = msg_class(StringClass, "newWithString", "oh hai");

	String st = msg_class(StringClass, "newWithFormat", "test %@ %d %f", ohhai, 5, 4.0);
	msg(SystemOut, "println", "%@", st);
	msg(st, "release");

	msg(ohhai, "release");

	File f = msg_class(FileClass, "newWithFilename", "../README.md");
	Scanner s = msg_class(ScannerClass, "newWithFile", f);
	Integer hasNext = msg_class(IntegerClass, "newWithInt", 1);
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

	Foo mys = msg_class(FooClass, "new", 77, "Foo");
	msg(mys, "concatenate", " Fighters");
	msg(SystemOut, "println", "%@", mys);
	msg(mys, "release");

	Stack stack = msg_class(StackClass, "new");
	msg(stack, "push", msg_class(StringClass, "newWithString", "Ryan"));
	msg(stack, "push", msg_class(StringClass, "newWithString", "Tanner"));
	msg(stack, "pop");
	String str = msg(stack, "peek");
	if (str) {
		msg(SystemOut, "println", "%@", str);
	}
	stack = msg(stack, "release");
}
