
#include "CBang.h"
#include "CBNull.h"

Class NullClass = NULL;

static void *new(void *v, va_list *args);

static void *init(void *v, va_list *args);
static void *dealloc(void *v, va_list *args);

void null_class_init() {
	NullClass = msg_class(ClassClass, "new", "Null", ObjectClass);

	push_back(NullClass->static_methods, mmethod("new", &new));
	
	push_back(NullClass->instance_methods, mmethod("init", &init));
	push_back(NullClass->instance_methods, mmethod("dealloc", &dealloc));
}

void *new(void *v, va_list *args) {
	Null o = cballoc(sizeof(struct _CBNull));
	init(o, args);
	((Object)o)->root = NullClass;
	return o;
}

void *init(void *v, va_list *args) {
	Null o = (Null)v;
	msg_cast(ObjectClass, o, "init");
	return o;
}

void *dealloc(void *v, va_list *args) {
	Null o = (Null)v;
	return msg_cast(ObjectClass, o, "release");
}
