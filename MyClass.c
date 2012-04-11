
#include "CBang.h"
#include "CBString.h"
#include "MyClass.h"

static class this = NULL;

static void *constructor(va_list args);
static void *print(void *v, va_list args);

class myclass_init() {
	method m;

	if (this) {
		return this;
	}

	this = mclass(mstring("MyClass"), mstring("CBString"), &constructor, NULL);

	m = mmethod(mstring("print"), &print);
	push_back(this->methods, m);

	return this;
}

void *constructor(va_list args) {
	MyClass v = malloc(sizeof(struct _MyClass));
	assert(v);
	var meta = (var)v;
	meta->type = this;
	meta->parent = NULL;

	v->value = va_arg(args, int);

	return v;
}

void *print(void *v, va_list args) {
	MyClass m = (MyClass)v;
	printf("%d", m->value);
	return NULL;
}