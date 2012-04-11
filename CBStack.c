
#include "CBang.h"
#include "CBStack.h"

static class this = NULL;

static void *constructor(void *v, void **p, va_list args);
static void destructor(void *v);
static void *super(void *v);

static void *push(void *v, va_list args);
static void *pop(void *v, va_list args);
static void *peek(void *v, va_list args);

class cbstack_init() {
	method m;

	if (this) {
		return this;
	}

	this = mclass(mstring("CBStack"), NULL, &constructor, &destructor, &super);

	m = mmethod(mstring("push"), &push);
	push_back(this->methods, m);
	m = mmethod(mstring("pop"), &pop);
	push_back(this->methods, m);
	m = mmethod(mstring("peek"), &peek);
	push_back(this->methods, m);

	return this;
}

void *constructor(void *v, void **p, va_list args) {
	CBStack s;
	if (!v) {
		s = malloc(sizeof(struct _CBStack));
		assert(s);
	}  else {
		s = (CBStack)s;
	}

	s->type = this;
	s->llist = create_list();

	*p = &s->parent;

	return s;
}

void destructor(void *v) {
	CBStack s = (CBStack)v;
	empty_list(s->llist, &free);
}

void *super(void *v) {
	CBStack s = (CBStack)v;
	return &s->parent;
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

	void *retval = peek(s, NULL);
	remove_front(s->llist, &free);
	return retval;
}

void *peek(void *v, va_list args) {
	CBStack s = (CBStack)v;

	if (is_empty(s->llist)) {
		return NULL;
	}
	return front(s->llist);
}