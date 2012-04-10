
#include "CBang.h"

static class this = NULL;

static var constructor();
static var print();

class cbobject_init() {
	method m;

	if (this) {
		return this;
	}

	this = mclass(mstring("CBObject"), NULL, &constructor, NULL);

	m = mmethod(mstring("print"), &print);
	push_back(this->methods, m);

	return this;
}

var constructor(va_list args) {
	return mvar(this);
}

var print(var v, va_list args) {
	printf("CBObject");
	return NULL;
}