
#include "../libcbang/CBang.h"
#include "FooClass.h"

int main(int argc, char **argv) {
	cbinit();
	foo_class_init();

	Object o = msg_class(ObjectClass, "new");
	msg(o, "print");
	msg(o, "release");
	msg(SystemOut, "println", "");

	Null n = msg_class(NullClass, "new");
	msg(n, "print");
	msg(n, "release");
	msg(SystemOut, "println", "");

	String ohhai = msg_class(StringClass, "newWithString", "oh hai");

	String st = msg_class(StringClass, "newWithFormat", "test %@ %d %f", ohhai, 5, 4.0);
	msg(st, "print");
	msg(st, "release");
	msg(SystemOut, "println", "");

	msg(ohhai, "release");

	File f = msg_class(FileClass, "newWithFilename", "../README.md");
	Scanner s = msg_class(ScannerClass, "newWithFile", f);
	Integer i = msg_class(IntegerClass, "newWithInt", 1);
	while (!msg(i, "equals", 0)) {
		String token = msg(s, "next");
		msg(SystemOut, "print", "%@ ", token);
		msg(token, "release");

		msg(i, "release");
		i = msg(s, "has_next");
	}
	msg(i, "release");
	msg(s, "release");
	msg(f, "release");
	msg(SystemOut, "println", "");

	Foo mys = msg_class(FooClass, "new", 77, "Foo");
	msg(mys, "concatenate", " Fighters");
	msg(mys, "print");
	msg(mys, "release");
	msg(SystemOut, "println", "");

	Stack stack = msg_class(StackClass, "new");
	msg(stack, "push", msg_class(StringClass, "newWithString", "Ryan"));
	msg(stack, "push", msg_class(StringClass, "newWithString", "Tanner"));
	msg(stack, "pop");
	String str = msg(stack, "peek");
	if (str) {
		msg(SystemOut, "println", "%@", str);
	}
	stack = msg(stack, "release");

	msg(SystemOut, "println", "");
}
