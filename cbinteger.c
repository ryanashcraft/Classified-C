
#include "CBang.h"
#include "CBInteger.h"

static class this = NULL;

static void *constructor(va_list args);

int cbinteger_to_int(CBInteger i) {
	return i->value;
}

class cbinteger_init() {
	if (this) {
		return this;
	}

	this = mclass(mstring("CBInteger"), NULL, &constructor, NULL);

	return this;
}

void *constructor(va_list args) {
	CBInteger i = malloc(sizeof(struct _CBInteger));
	assert(i);
	i->meta.type = this;
	i->meta.parent = NULL;

	i->value = va_arg(args, int);

	return i;
}