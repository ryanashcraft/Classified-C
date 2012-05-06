
#include "CBang.h"
#include "CBNull.h"

Class NullClass = NULL;

typedef struct _CBNull {
	struct _CBObject base;
} *Null;

static void *new(void *v, va_list *args);

static void *init(void *v, va_list *args);
static void *dealloc(void *v, va_list *args);

void null_class_init() {
	NullClass = msg(ClassClass, "new", "Null", ObjectClass);
	NullClass->base.root = NullClass;
	NullClass->base.parent = ClassClass;

	push_back(NullClass->static_methods, mmethod("new", &new));
	
	push_back(NullClass->instance_methods, mmethod("init", &init));
	push_back(NullClass->instance_methods, mmethod("dealloc", &dealloc));
}

void *new(void *v, va_list *args) {
	Null o = cballoc(sizeof(struct _CBNull));
	init(o, args);
	return o;
}

void *init (void *v, va_list *args) {
	Null o = (Null)v;
	object_init(o, NullClass);
	o->base.parent = NullClass;
	return o;
}

void *dealloc(void *v, va_list *args) {
	Null o = (Null)v;
	free(o);
	return NULL;
}
