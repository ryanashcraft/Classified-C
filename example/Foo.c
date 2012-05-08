
#include "../libcbang/CBang.h"
#include "FooClass.h"

int main(int argc, char **argv) {
	cbinit();
	foo_class_init();

	Object o = msg_class(ObjectClass, "new");
	String description = msg(o, "description");
	msg(SystemOut, "println", "%@", description);
	msg(o, "release");
	msg(description, "release");

	Null n = msg_class(NullClass, "new");
	description = msg(o, "description");
	msg(SystemOut, "println", "%@", description);
	msg(description, "release");
	msg(n, "release");

	String ohhai = msg_class(StringClass, "newWithString", "oh hai");

	String st = msg_class(StringClass, "newWithFormat", "test %@ %d %f", ohhai, 5, 4.0);
	description = msg(st, "description");
	msg(SystemOut, "println", "%@", description);
	msg(description, "release");
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
	msg(SystemOut, "println", "");

	Foo mys = msg_class(FooClass, "new", 77, "Foo");
	msg(mys, "concatenate", " Fighters");
	description = msg(mys, "description");
	msg(SystemOut, "println", "%@", description);
	msg(description, "release");
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
