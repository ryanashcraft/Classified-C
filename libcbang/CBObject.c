
#include "CBang.h"
#include "CBObject.h"

Class ObjectClass = NULL;

static void *new(void *v, va_list *args);

static void *init(void *v, va_list *args);
static void *release(void *v, va_list *args);
static void *dealloc(void *v, va_list *args);
static void *retain(void *v, va_list *args);
static void *description(void *v, va_list *args);

void object_class_init() {
	ObjectClass = new_class("Object", NULL);

	push_back(ObjectClass->static_methods, mmethod("new", &new));

	push_back(ObjectClass->instance_methods, mmethod("init", &init));
	push_back(ObjectClass->instance_methods, mmethod("release", &release));
	push_back(ObjectClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(ObjectClass->instance_methods, mmethod("retain", &retain));
	push_back(ObjectClass->instance_methods, mmethod("description", &description));
}

Object object_init(void *v) {
	Object o = (Object)v;
	return o;
}

void *new(void *v, va_list *args) {
	Object o = cballoc(sizeof(struct _CBObject));
	object_init(o);
	o->root = ObjectClass;
	return o;
}

void *init(void *v, va_list *args) {
	return object_init(v);
}

void *release(void *v, va_list *args) {
	Object o = (Object)v;
	--o->retaincount;

	if (o->retaincount == 0) {
		return msg(o, "dealloc");
	}

	return o;
}

void *dealloc(void *v, va_list *args) {
	free(v);
	return NULL;
}

void *retain(void *v, va_list *args) {
	Object o = (Object)v;
	o->retaincount++;
	return o;
}

void *description(void *v, va_list *args) {
	return msg_class(StringClass, "newWithString", "Object");
}
