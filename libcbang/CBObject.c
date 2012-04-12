
#include "CBang.h"
#include "CBObject.h"

static class this = NULL;

static void *constructor(void *v, void **p, va_list *args);
void *print(void *v, va_list *args);

class cbobject_init() {
	method m;

	if (this) {
		return this;
	}

	this = mclass(mstring("CBObject"), NULL, &constructor, NULL, NULL);

	m = mmethod(mstring("print"), &print);
	push_back(this->methods, m);

	return this;
}

void *constructor(void *v, void **p, va_list *args) {
	CBObject o;
	if (!v) {
		o = malloc(sizeof(struct _CBObject));
		assert(o);
	} else {
		o = (CBObject)v;
	}
	o->type = this;

	*p = NULL;

	return o;
}

void *print(void *v, va_list *args) {
	printf("CBObject");
	return NULL;
}