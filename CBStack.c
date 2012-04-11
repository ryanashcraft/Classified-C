
#include "CBang.h"
#include "CBStack.h"

static class this = NULL;

static void *constructor(va_list args);
static void destructor(void *v);
static void *push(void *v, va_list args);
static void *pop(void *v, va_list args);
static void *peek(void *v, va_list args);

typedef struct _local {
	list *llist;
} *local;

class cbstack_init() {
	method m;

	if (this) {
		return this;
	}

	this = mclass(mstring("CBStack"), NULL, &constructor, &destructor);

	m = mmethod(mstring("push"), &push);
	push_back(this->methods, m);
	m = mmethod(mstring("pop"), &pop);
	push_back(this->methods, m);
	m = mmethod(mstring("peek"), &peek);
	push_back(this->methods, m);

	return this;
}

void *constructor(va_list args) {
	CBStack v = malloc(sizeof(struct _local));
	assert(v);
	v->meta.type = this;
	v->meta.parent = NULL;

	v->llist = create_list();

	return v;
}

void destructor(void *v) {
	CBStack s = (CBStack)v;
	empty_list(s->llist, &free);
}

void *push(void *v, va_list args) {
	CBStack s = (CBStack)v;

	void *data = va_arg(args, void *);
	push_front(s->llist, data);
	return NULL;
}

void *pop(void *v, va_list args) {
	CBStack s = (CBStack)v;

	if (is_empty(s->llist)) {
		return NULL;
	}

	var retval = peek(v, NULL);
	remove_front(s->llist, NULL);
	return retval;
}

void *peek(void *v, va_list args) {
	CBStack s = (CBStack)v;

	if (is_empty(s->llist)) {
		return NULL;
	}
	return front(s->llist);
}