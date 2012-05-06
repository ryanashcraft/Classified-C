
#include "../libcbang/CBang.h"
#include "FooClass.h"

Class FooClass = NULL;

static void *new(void *v, va_list *args);

static void *init(void *v, va_list *args);
static void *dealloc(void *v, va_list *args);
static void *print(void *v, va_list *args);

void foo_class_init() {
	FooClass = msg(ClassClass, "new", "Foo", StringClass);

	push_back(FooClass->static_methods, mmethod("new", &new));

	push_back(FooClass->instance_methods, mmethod("init", &init));
	push_back(FooClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(FooClass->instance_methods, mmethod("print", &print));
}

void *new(void *v, va_list *args) {
	Foo o = cballoc(sizeof(struct _Foo));
	init(o, args);
	((Object)o)->root = FooClass;
	return o;
}

void *init(void *v, va_list *args) {
	Foo o = (Foo)v;
	int value = va_arg(*args, int);
	object_init(o, FooClass);
	msg(o, "initWithString", va_arg(*args, string));
	o->value = value;
	return o;
}

void *dealloc(void *v, va_list *args) {
	Foo o = (Foo)v;
	free(o);	
	return o;
}

void *print(void *v, va_list *args) {
	Foo o = (Foo)v;
	printf("%d ", o->value);
	msg_super(o, "print");
	return NULL;
}
