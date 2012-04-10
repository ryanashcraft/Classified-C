
#include "CBang.h"

static class this = NULL;

static var constructor();
static var print();

class cbobject_init() {
	method m;

	if (this) {
		return this;
	}

	this = mclass(mstring("CBObject"), NULL, &constructor);

	m = mmethod(mstring("print"), &print);
	push_back(this->methods, m);

	return this;
}

var constructor(va_list args) {
	return mvar(this);
}

var print(va_list args) {
	printf("FOO!\n");
	return NULL;
}