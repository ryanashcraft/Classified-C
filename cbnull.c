
#include "CBang.h"
#include "CBNull.h"

static class this = NULL;

static void *constructor(va_list args);

class cbnull_init() {
	if (this) {
		return this;
	}

	this = mclass(mstring("CBNull"), NULL, &constructor, NULL);

	return this;
}

void *constructor(va_list args) {
	CBNull v = malloc(sizeof(struct _CBNull));
	assert(v);
	v->meta.type = this;
	v->meta.parent = NULL;

	return v;
}