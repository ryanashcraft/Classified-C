
#include "../libcbang/CBang.h"
#include "FooClass.h"

int main(int argc, char **argv) {
	cbang_init();
	foo_class_init();

	var o = message(ObjectClass, "init", NULL);
	message(o, "print");
	o = message(o, "release");
	printf("\n");

	var st = message(StringClass, "initWithString", NULL, "test");
	message(st, "print");
	st = message(st, "release");
	printf("\n");

	var f = message(FileClass, "initWithFilename", NULL, "../README.md");
	var s = message(ScannerClass, "initWithFile", NULL, f);
	var i = message(IntegerClass, "initWithInt", NULL, 1);
	while (!message(i, "equals", 0)) {
		var token = message(s, "next");
		fprintf(stderr, "%s ", (string)message(token, "toCString"));
		message(token, "release");

		i = message(i, "release");
		i = message(s, "has_next");
	}
	i = message(i, "release");
	s = message(s, "release");
	f = message(f, "release");
	printf("\n");

	var n = message(NullClass, "init", NULL);
	message(n, "print");
	printf("\n");
	n = message(n, "release");

	var ohhai = message(StringClass, "initWithString", NULL, "OH HAI!");
	message(ohhai, "print");
	printf("\n");
	ohhai = message(ohhai, "release");

	Foo mys = message(FooClass, "init", NULL, 77, "Foo");
	message(mys, "concatenate", " Fighters");
	message(mys, "print");
	printf("\n");

	i = message(mys, "length");
	printf("Length of string: %ld\n", (long)message(i, "toCInt"));
	i = message(i, "release");
	mys = message(mys, "retain");
	mys = message(mys, "release");
	i = message(mys, "length");
	mys = message(mys, "release");

	var stack = message(StackClass, "init", NULL);
	message(stack, "push", message(StringClass, "initWithString", NULL, "Ryan"));
	message(stack, "push", message(StringClass, "initWithString", NULL, "Tanner"));
	message(stack, "pop");
	var str = message(stack, "peek");
	if (str) {
		printf("%s\n", (string)message(str, "toCString"));
	}
	stack = message(stack, "release");

	printf("\n");
}
