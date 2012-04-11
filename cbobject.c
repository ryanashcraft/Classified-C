
#include "CBang.h"
#include "CBObject.h"

static class this = NULL;

static void *constructor(va_list args);
void *print(void *v, va_list args);

class cbobject_init() {
	method m;

	if (this) {
		return this;
	}

	this = mclass(mstring("CBObject"), NULL, &constructor, NULL);

	m = mmethod(mstring("print"), &print);
	push_back(this->methods, m);

	return this;
}

void *constructor(va_list args) {
	CBObject v = malloc(sizeof(struct _CBObject));
	assert(v);
	v->meta.type = this;
	v->meta.parent = NULL;

	return v;
}

void *print(void *v, va_list args) {
	printf("CBObject");
	return NULL;
}