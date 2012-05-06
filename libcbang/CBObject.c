
#include "CBang.h"
#include "CBObject.h"

Class ObjectClass = NULL;

static void *new(void *v, va_list *args);

static void *init(void *v, va_list *args);
static void *release(void *v, va_list *args);
static void *dealloc(void *v, va_list *args);
static void *retain(void *v, va_list *args);
static void *print(void *v, va_list *args);

void object_class_init() {
	ObjectClass = new_class("Object", NULL);
	object_init(ObjectClass, ClassClass);
	ObjectClass->base.root = ObjectClass;

	push_back(ObjectClass->static_methods, mmethod("new", &new));

	push_back(ObjectClass->instance_methods, mmethod("init", &init));
	push_back(ObjectClass->instance_methods, mmethod("release", &release));
	push_back(ObjectClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(ObjectClass->instance_methods, mmethod("retain", &retain));
	push_back(ObjectClass->instance_methods, mmethod("print", &print));
}

Object object_init(void *v, Class parent) {
	Object o = (Object)v;

	o->class = ObjectClass;
	if (o->root == NULL && parent != NULL)
		o->root = parent;
	else
		o->root = ObjectClass;
	o->parent = parent;

	return o;
}

void *new(void *v, va_list *args) {
	Object o = cballoc(sizeof(struct _CBObject));
	object_init(o, NULL);
	return o;
}

void *init(void *v, va_list *args) {
	Class parent = va_arg(*args, Class);
	return object_init(v, parent);
}

void *release(void *v, va_list *args) {
	Object o = (Object)v;
	--o->retaincount;

	if (o->retaincount == 0) {
		return msg(o, "dealloc");
	}

	return o->root;
}

void *dealloc(void *v, va_list *args) {
	free(v);
	return NULL;
}

void *retain(void *v, va_list *args) {
	Object o = (Object)v;
	o->retaincount++;
	return o->root;
}

void *print(void *v, va_list *args) {
	fprintf(stderr, "Object");
	return v;
}

