
#include "CBang.h"
#include "CBNull.h"

Class NullClass = NULL;

static void *init(void *v, va_list *args);

static void *release(void *v, va_list *args);

void null_class_init() {
	method m;

	NullClass = message(ClassClass, "init", "NullClass", ObjectClass);

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

	n->parent = message(ObjectClass, "init");

	return n;
}

void *release(void *v, va_list *args) {
	Null n = (Null)v;
	message(n->parent, "release");
	free_list(n->methods, free);
	free(n);
	return n;
}
