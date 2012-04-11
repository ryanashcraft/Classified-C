
#include "CBang.h"
#include "CBInteger.h"

static class this = NULL;

static void *constructor(void *v, void **p, va_list args);
static void *super(void *v);

class cbinteger_init() {
	if (this) {
		return this;
	}

	this = mclass(mstring("CBInteger"), NULL, &constructor, NULL, &super);

	return this;
}

void *constructor(void *v, void **p, va_list args) {
	CBInteger i;
	if (!v) {
		i = malloc(sizeof(struct _CBInteger));
		assert(i);
	} else {
		i = (CBInteger)i;
	}

	i->type = this;
	i->value = va_arg(args, int);

	*p = &i->parent;

	return i;
}

void *super(void *v) {
	CBInteger i = (CBInteger)v;
	return &i->parent;
}