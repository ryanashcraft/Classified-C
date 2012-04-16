
#include "CBang.h"
#include "CBNull.h"

Class NullClass = NULL;

static void *init(void *v, va_list *args);
static void *super(void *v);

static void *release(void *v, va_list *args);

void null_class_init() {
	method m;

	NullClass = message(ClassClass, "init", "NullClass", ObjectClass, &super);

	m = mmethod("init", &init);
	push_back(NullClass->methods, m);
}

void *init(void *v, va_list *args) {
	Null n;
	method m;

	n = calloc(1, sizeof(struct _CBNull));
	assert(n);

	n->class = NullClass;

	n->methods = create_list();
	m = mmethod("release", &release);
	push_back(n->methods, m);

	message(ObjectClass, "initWithPointer", &(n->parent));

	return n;
}

void *super(void *v) {
	Null n = (Null)v;
	return &(n->parent);
}

void *release(void *v, va_list *args) {
	Null n = (Null)v;
	message(super(n), "release");
	free_list(n->methods, free);
	free(n);
	return n;
}
