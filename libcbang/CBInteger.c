
#include "CBang.h"
#include "CBInteger.h"

Class IntegerClass = NULL;

static void *initWithInt(void *v, va_list *args);

static void *dealloc(void *v, va_list *args);

void integer_class_init() {
	IntegerClass = message(ClassClass, "init", "Integer", ObjectClass);

	push_back(IntegerClass->methods, mmethod("initWithInt", &initWithInt));
	
	push_back(IntegerClass->instance_methods, mmethod("dealloc", &dealloc));
}

void *initWithInt(void *v, va_list *args) {
	Integer o;

	o = calloc(1, sizeof(struct _CBInteger));
	assert(o);

	Object root = va_arg(*args, Object);
	if (!root) {
		root = (Object)o;
	}

	o->class = IntegerClass;
	o->methods = IntegerClass->instance_methods;
	o->parent = message(ObjectClass, "init", root);
	o->root = root;

	o->value = va_arg(*args, int);

	return o;
}

void *dealloc(void *v, va_list *args) {
	Integer o = (Integer)v;
	message(o->parent, "dealloc");
	free(o);
	return NULL;
}