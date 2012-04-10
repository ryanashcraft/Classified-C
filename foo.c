
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
	release(n);

	var mys = construct("MyClass", 77, mstring("Foo"));
	message(mys, "concatenate", mstring(" Fighters"));
	message(mys, "print");
	printf("\n");
	message(mys->parent, "print");
	printf("\n");

	var i = message(mys, "length");
	printf("Length of string \"%s\": %d\n", cbstring_to_string(mys->parent), cbinteger_to_int(i));
	release(i);

	release(mys);
}