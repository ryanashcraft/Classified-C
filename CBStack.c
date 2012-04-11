
#include "CBang.h"
#include "CBStack.h"

static class this = NULL;

static var constructor(va_list args);
static void destructor(var v);
static var push(var v, va_list args);
static var pop(var v, va_list args);
static var peek(var v, va_list args);

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

var constructor(va_list args) {
	var v = mvar(this);

	v->data = malloc(sizeof(struct _local));
	((local)v->data)->llist = create_list();

	return v;
}

void destructor(var v) {
	empty_list(((local)v->data)->llist, &free);
}

var push(var v, va_list args) {
	void *data = va_arg(args, void *);
	push_front(((local)v->data)->llist, data);
	return NULL;
}

var pop(var v, va_list args) {
	if (is_empty(((local)v->data)->llist)) {
		return NULL;
	}

	var retval = peek(v, NULL);
	remove_front(((local)v->data)->llist, NULL);
	return retval;
}

var peek(var v, va_list args) {
	if (is_empty(((local)v->data)->llist)) {
		return NULL;
	}
	return front(((local)v->data)->llist);
}