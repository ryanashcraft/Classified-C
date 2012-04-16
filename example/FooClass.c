
#include "../libcbang/CBang.h"
#include "FooClass.h"

Class FooClass = NULL;

static void *init(void *v, va_list *args);

static void *release(void *v, va_list *args);
static void *print(void *v, va_list *args);

void foo_class_init() {
	method m;

	FooClass = message(ClassClass, "init", "FooClass", StringClass);

	m = mmethod("init", &init);
	push_back(FooClass->methods, m);

	m = mmethod("release", &release);
	push_back(FooClass->instance_methods, m);
	m = mmethod("print", &print);
	push_back(FooClass->instance_methods, m);
}

void *init(void *v, va_list *args) {
	Foo o;

	o = calloc(1, sizeof(struct _MyClass));
	assert(o);

	o->class = FooClass;
	o->methods = FooClass->instance_methods;
	o->parent = message(StringClass, "initWithString", args);

	o->value = va_arg(*args, int);

	return o;
}

void *release(void *v, va_list *args) {
	Foo o = (Foo)v;
	message(o->parent, "release");
	free(o);
	return o;
}

void *print(void *v, va_list *args) {
	Foo o = (Foo)v;
	printf("%d ", o->value);
	message(o->parent, "print");
	return NULL;
}
