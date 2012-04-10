
#include "CBang.h"
#include "CBString.h"
#include "MyClass.h"

static class this = NULL;

static var constructor();
static var print();

class myclass_init() {
	method m;

	if (this) {
		return this;
	}

	this = mclass(mstring("MyClass"), mstring("CBString"), &constructor);

	m = mmethod(mstring("print"), &print);
	push_back(this->methods, m);

	return this;
}

var constructor(va_list args) {
	var v = mvar(this);

	v->data = malloc(sizeof(struct _myclass_data));
	((myclass_data)v->data)->value = va_arg(args, int);

	return v;
}

var print(var v, va_list args) {
	printf("%d", ((myclass_data)v->data)->value);
	return NULL;
}