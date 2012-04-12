
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

	string oij = mstring("OH HAI!");
	CBString s = construct("CBString", oij);
	message(s, "print");
	printf("\n");
	destruct(s);

	oij = mstring("Foo");
	MyClass mys = construct("MyClass", 77, oij);
	message(mys, "concatenate", mstring(" Fighters"));
	message(mys, "print");
	printf("\n");

	CBInteger i = message(mys, "length");
	printf("Length of string: %d\n", i->value);
	destruct(i);
	destruct(mys);

	CBStack stack = construct("CBStack");
	message(stack, "push", construct("CBString", mstring("Ryan")));
	message(stack, "push", construct("CBString", mstring("Tanner")));
	message(stack, "pop");
	// message(stack, "pop");
	s = message(stack, "peek");
	if (s) {
		printf("%s\n", s->value);
	}
	destruct(stack);
}