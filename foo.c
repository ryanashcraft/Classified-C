
#include "CBang.h"
#include "CBString.h"
#include "CBInteger.h"
#include "MyClass.h"

int main(int argc, char **argv) {
	cbang_init();
	add_class(myclass_init());

	var n = construct("CBNull");
	message(n, "print");
	printf("\n");
	destruct(n);

	var mys = construct("MyClass", 77, mstring("Foo"));
	message(mys, "concatenate", mstring(" Fighters"));
	message(mys, "print");
	printf("\n");
	message(mys->parent, "print");
	printf("\n");

	var i = message(mys, "length");
	printf("Length of string \"%s\": %d\n", cbstring_to_string(mys->parent), cbinteger_to_int(i));
	destruct(i);

	var stack = construct("CBStack");
	message(stack, "push", construct("CBString", mstring("Ryan")));
	message(stack, "push", construct("CBString", mstring("Tanner")));
	message(stack, "pop");
	message(stack, "pop");
	printf("%s\n", cbstring_to_string(message(stack, "peek")));

	destruct(mys);
}