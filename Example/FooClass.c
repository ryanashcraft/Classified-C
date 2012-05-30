
#include "../libclassc/Classified-C.h"
#include "FooClass.h"

Class FooClass = NULL;

static void *new(void *v, va_list *args);

static void *init(void *v, va_list *args);
static void *dealloc(void *v, va_list *args);
static void *description(void *v, va_list *args);

void foo_class_init() {
	FooClass = msg(ClassClass, "new", "Foo", StringClass);

	push_back(FooClass->static_methods, mmethod("new", &new));

	push_back(FooClass->instance_methods, mmethod("init", &init));
	push_back(FooClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(FooClass->instance_methods, mmethod("description", &description));
}

void *new(void *v, va_list *args) {
	Foo o = cc_alloc(sizeof(struct _Foo));
	init(o, args);
	((Object)o)->root = FooClass;
	return o;
}

void *init(void *v, va_list *args) {
	Foo o = (Foo)v;
	int value = va_arg(*args, int);
	msg_cast(ObjectClass, o, "init");
	msg_cast(StringClass, o, "initWithCString", va_arg(*args, cstring));

	o->value = value;

	return o;
}

void *dealloc(void *v, va_list *args) {
	Foo o = (Foo)v;
	return msg_cast(StringClass, o, "dealloc");
}

void *description(void *v, va_list *args) {
	Foo o = (Foo)v;
	return msg(StringClass, "newWithFormatCString", "%d %@", o->value, o);
}
