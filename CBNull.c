
#include "CBang.h"
#include "CBNull.h"

static class this = NULL;

static void *constructor(void *v, void **p, va_list args);
static void *super(void *v);

class cbnull_init() {
	if (this) {
		return this;
	}

	this = mclass(mstring("CBNull"), NULL, &constructor, NULL, &super);

	return this;
}

void *constructor(void *v, void **p, va_list args) {
	CBNull n;
	if (!v) {
		n = calloc(1, sizeof(struct _CBNull));
		assert(n);
	} else {
		n = (CBNull)v;
	}
	n->type = this;

	*p = &n->parent;

	return n;
}

void *super(void *v) {
	CBNull n = (CBNull)v;
	return &n->parent;
}