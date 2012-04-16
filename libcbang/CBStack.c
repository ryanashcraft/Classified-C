
#include "CBang.h"
#include "CBStack.h"

Class StackClass = NULL;

static void *init(void *v, va_list *args);
static void *super(void *v);

static void *release(void *v, va_list *args);
static void *push(void *v, va_list *args);
static void *pop(void *v, va_list *args);
static void *peek(void *v, va_list *args);

void stack_class_init() {
	method m;

	StackClass = message(ClassClass, "init", "StackClass", ObjectClass, &super);

	m = mmethod(mstring("init"), &init);
	push_back(StackClass->methods, m);
}

void *init(void *v, va_list *args) {
	Stack s;
	method m;

	s = malloc(sizeof(struct _CBStack));
	assert(s);

	s->class = StackClass;
	s->llist = create_list();

	s->methods = create_list();
	m = mmethod(mstring("release"), &release);
	push_back(s->methods, m);
	m = mmethod(mstring("push"), &push);
	push_back(s->methods, m);
	m = mmethod(mstring("pop"), &pop);
	push_back(s->methods, m);
	m = mmethod(mstring("peek"), &peek);
	push_back(s->methods, m);

	message(ObjectClass, "initWithPointer", &(s->parent));

	return s;
}

void *super(void *v) {
	Stack s = (Stack)v;
	return &(s->parent);
}

void *release(void *v, va_list *args) {
	Stack s = (Stack)v;
	empty_list(s->llist, &free);
	return s;
}

void *push(void *v, va_list *args) {
	Stack s = (Stack)v;

	void *data = va_arg(*args, void *);
	push_front(s->llist, data);
	return NULL;
}

void *pop(void *v, va_list *args) {
	Stack s = (Stack)v;

	if (is_empty(s->llist)) {
		return NULL;
	}

	void *retval = peek(s, NULL);
	remove_front(s->llist, &free);
	return retval;
}

void *peek(void *v, va_list *args) {
	Stack s = (Stack)v;

	if (is_empty(s->llist)) {
		return NULL;
	}
	return front(s->llist);
}