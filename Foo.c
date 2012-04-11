
#include "CBang.h"
#include "CBNull.h"
#include "CBString.h"
#include "CBInteger.h"
#include "CBStack.h"
#include "MyClass.h"

int main(int argc, char **argv) {
	cbang_init();
	add_class(myclass_init());

	CBNull n = construct("CBNull");
	message(n, "print");
	printf("\n");
	destruct(n);

	CBString s = construct("CBString", "OH HAI!");
	message(s, "print");
	printf("\n");

	MyClass mys = construct("MyClass", 77, "Foo");
	message(mys, "concatenate", " Fighters");
	message(mys, "print");
	printf("\n");

	CBInteger i = message(mys, "length");
	printf("Length of string: %d\n", i->value);
	destruct(i);

	CBStack stack = construct("CBStack");
	message(stack, "push", construct("CBString", "Ryan"));
	message(stack, "push", construct("CBString", "Tanner"));
	message(stack, "pop");
	// message(stack, "pop");
	s = message(stack, "peek");
	if (s) {
		printf("%s\n", s->value);
	}

	destruct(mys);
}