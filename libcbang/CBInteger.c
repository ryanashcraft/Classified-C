
#include "CBang.h"
#include "CBInteger.h"

Class IntegerClass = NULL;

typedef struct _CBInteger {
	OBJECT_BASE
	
	size_t value;
} *Integer;

static void *initWithInt(void *v, va_list *args);

static void *dealloc(void *v, va_list *args);
static void *toCInt(void *v, va_list *args);
static void *equals(void *v, va_list *args);

void integer_class_init() {
	IntegerClass = msg(ClassClass, "init", "Integer", ObjectClass);

	push_back(IntegerClass->methods, mmethod("initWithInt", &initWithInt));
	
	push_back(IntegerClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(IntegerClass->instance_methods, mmethod("toCInt", &toCInt));
	push_back(IntegerClass->instance_methods, mmethod("equals", &equals));
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
	o->parent = msg(ObjectClass, "init", root);
	o->root = root;

	o->value = va_arg(*args, size_t);

	return o;
}

void *dealloc(void *v, va_list *args) {
	Integer o = (Integer)v;
	msg(o->parent, "dealloc");
	free(o);
	return NULL;
}

void *toCInt(void *v, va_list *args) {
	Integer o = (Integer)v;
	return (void *)o->value;
}

void *equals(void *v, va_list *args) {
	Integer o = (Integer)v;
	size_t other = va_arg(*args, size_t);

	if (o->value == other) {
		return YES;
	}

	return NO;
}
