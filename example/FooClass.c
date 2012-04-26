
#include "../libcbang/CBang.h"
#include "FooClass.h"

Class FooClass = NULL;

typedef struct _Foo {
	OBJECT_BASE

	int value;
} *Foo;

static void *init(void *v, va_list *args);

static void *dealloc(void *v, va_list *args);
static void *print(void *v, va_list *args);

void foo_class_init() {
	// Define FooClass
	FooClass = message(ClassClass, "init", "Foo", StringClass);

	// Register static methods
	push_back(FooClass->methods, mmethod("init", &init));

	// Register instance methods
	push_back(FooClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(FooClass->instance_methods, mmethod("print", &print));
}

void *init(void *v, va_list *args) {
	// Allocate
	Foo o = calloc(1, sizeof(struct _Foo));
	assert(o);

	Object root = va_arg(*args, Object);
	if (!root) {
		root = (Object)o;
	}

	int value = va_arg(*args, int);

	// Set instance variables
	o->class = FooClass;
	o->methods = FooClass->instance_methods;
	o->parent = message(StringClass, "initWithString", root, va_arg(*args, string));
	o->root = root;

	o->value = value;

	return o;
}

void *dealloc(void *v, va_list *args) {
	Foo o = (Foo)v;
	message(o->parent, "dealloc");
	free(o);	
	return o;
}

void *print(void *v, va_list *args) {
	Foo o = (Foo)v;
	printf("%d ", o->value);
	message(o->parent, "print");
	return NULL;
}
