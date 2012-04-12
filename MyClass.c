
#include "CBang.h"
#include "CBString.h"
#include "MyClass.h"

static class this = NULL;

static void *constructor(void *v, void **p, va_list *args);
static void *super(void *v);

static void *print(void *v, va_list *args);

class myclass_init() {
	method m;

	if (this) {
		return this;
	}

	this = mclass(mstring("MyClass"), mstring("CBString"), &constructor, NULL, &super);

	m = mmethod(mstring("print"), &print);
	push_back(this->methods, m);

	return this;
}

void *constructor(void *v, void **p, va_list *args) {
	MyClass m;
	if (!v) {
		m = malloc(sizeof(struct _MyClass));
		assert(m);
	} else {
		m = (MyClass)v;
	}

	m->type = this;
	m->value = va_arg(*args, int);

	*p = &m->parent;

	return m;
}

void *super(void *v) {
	MyClass m = (MyClass)v;
	return &m->parent;
}

void *print(void *v, va_list *args) {
	MyClass m = (MyClass)v;
	printf("%d ", m->value);

	message(super(m), "print");

	return NULL;
}