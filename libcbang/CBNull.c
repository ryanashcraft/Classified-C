
#include "CBang.h"
#include "CBNull.h"

Class NullClass = NULL;

typedef struct _CBNull {
	OBJECT_BASE
} *Null;

static void *init(void *v, va_list *args);

static void *dealloc(void *v, va_list *args);

void null_class_init() {
	NullClass = msg(ClassClass, "init", "Null", ObjectClass);

	push_back(NullClass->methods, mmethod("init", &init));
	
	push_back(NullClass->instance_methods, mmethod("dealloc", &dealloc));
}

void *init(void *v, va_list *args) {
	Null o;

	o = calloc(1, sizeof(struct _CBNull));
	assert(o);

	Object root = va_arg(*args, Object);
	if (!root) {
		root = (Object)o;
	}

	o->class = NullClass;
	o->methods = NullClass->instance_methods;
	o->parent = msg(ObjectClass, "init", root);
	o->root = root;

	return o;
}

void *dealloc(void *v, va_list *args) {
	Null o = (Null)v;
	msg(o->parent, "dealloc");
	free(o);
	return NULL;
}
