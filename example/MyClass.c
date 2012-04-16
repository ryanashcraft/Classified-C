
#include "../libcbang/CBang.h"
#include "MyClass.h"

Class FooClass = NULL;

static void *initWithInt(void *v, va_list *args);

static void *print(void *v, va_list *args);

void foo_class_init() {
	method m;

	FooClass = message(ClassClass, "init", StringClass, "FooClass");

	m = mmethod(mstring("initWithInt"), &initWithInt);
	push_back(FooClass->methods, m);
}

void *initWithInt(void *v, va_list *args) {
	Foo f;
	method m;

	if (!v) {
		f = malloc(sizeof(struct _MyClass));
		assert(f);
	} else {
		f = (Foo)v;
	}

	f->class = FooClass;
	f->value = va_arg(*args, int);

	f->methods = create_list();
	m = mmethod(mstring("print"), &print);
	push_back(f->methods, m);

	message(ObjectClass, "init", &(f->parent));

	return f;
}

void *print(void *v, va_list *args) {
	Foo f = (Foo)v;
	printf("%d ", f->value);

	message(&(f->parent), "print");

	return NULL;
}
