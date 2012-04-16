
#include "../libcbang/CBang.h"
#include "FooClass.h"

Class FooClass = NULL;

static void *init(void *v, va_list *args);

static void *release(void *v, va_list *args);
static void *print(void *v, va_list *args);

void foo_class_init() {
	// Define FooClass
	FooClass = message(ClassClass, "init", "Foo", StringClass);

	// Register static methods
	push_back(FooClass->methods, mmethod("init", &init));

	// Register instance methods
	push_back(FooClass->instance_methods, mmethod("release", &release));
	push_back(FooClass->instance_methods, mmethod("print", &print));
}

void *init(void *v, va_list *args) {
	// Allocate
	Foo o = calloc(1, sizeof(struct _Foo));
	assert(o);

	// Set instance variables
	o->class = FooClass;
	o->methods = FooClass->instance_methods;
	o->value = va_arg(*args, int);
	o->parent = message(StringClass, "initWithString", va_arg(*args, string));

	return o;
}

void *release(void *v, va_list *args) {
	Foo o = (Foo)v;

	// Release parent
	message(o->parent, "release");

	// Free
	free(o);
	
	return o;
}

void *print(void *v, va_list *args) {
	Foo o = (Foo)v;
	printf("%d ", o->value);
	message(o->parent, "print");
	return NULL;
}
