
#include "CBang.h"
#include "CBNull.h"

Class NullClass = NULL;

static void *init(void *v, va_list *args);
static void *super(void *v);

void null_class_init() {
	method m;

	NullClass = message(ClassClass, "init", "NullClass", ObjectClass, &super);

	m = mmethod(mstring("init"), &init);
	push_back(NullClass->methods, m);
}

void *init(void *v, va_list *args) {
	Null n;

	if (!v) {
		n = calloc(1, sizeof(struct _CBNull));
		assert(n);
	} else {
		n = (Null)v;
	}

	n->class = NullClass;

	message(ObjectClass, "initWithPointer", &(n->parent));

	return n;
}

void *super(void *v) {
	Null n = (Null)v;
	return &(n->parent);
}