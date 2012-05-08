
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
		fprintf(stderr, "%s ", (string)msg(token, "toCString"));
		msg(token, "release");

		i = msg(i, "release");
		i = msg(s, "has_next");
	}
	i = msg(i, "release");
	s = msg(s, "release");
	f = msg(f, "release");
	msg(SystemOut, "println", "");

	// var n = msg(NullClass, "init", NULL);
	// msg(n, "print");
	// printf("\n");
	// n = msg(n, "release");

	// var ohhai = msg(StringClass, "initWithString", NULL, "OH HAI!");
	// msg(ohhai, "print");
	// printf("\n");
	// ohhai = msg(ohhai, "release");

	Foo mys = msg_class(FooClass, "new", 77, "Foo");
	msg(mys, "concatenate", " Fighters");
	msg(mys, "print");
	msg(mys, "release");
	msg(SystemOut, "println", "");

	// i = msg(mys, "length");
	// printf("Length of string: %ld\n", (long)msg(i, "toCInt"));
	// i = msg(i, "release");
	// mys = msg(mys, "retain");
	// mys = msg(mys, "release");
	// i = msg(mys, "length");
	// mys = msg(mys, "release");

	// var stack = msg(StackClass, "init", NULL);
	// msg(stack, "push", msg(StringClass, "initWithString", NULL, "Ryan"));
	// msg(stack, "push", msg(StringClass, "initWithString", NULL, "Tanner"));
	// msg(stack, "pop");
	// var str = msg(stack, "peek");
	// if (str) {
	// 	printf("%s\n", (string)msg(str, "toCString"));
	// }
	// stack = msg(stack, "release");

	msg(SystemOut, "println", "");
}
