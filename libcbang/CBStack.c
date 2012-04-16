
#include "CBang.h"
#include "CBStack.h"

Class StackClass = NULL;

static void *init(void *v, va_list *args);

static void *release(void *v, va_list *args);
static void *push(void *v, va_list *args);
static void *pop(void *v, va_list *args);
static void *peek(void *v, va_list *args);

void message_release(void *v);

void stack_class_init() {
	method m;

	StackClass = message(ClassClass, "init", "StackClass", ObjectClass);

	m = mmethod("init", &init);
	push_back(StackClass->methods, m);
}

void *init(void *v, va_list *args) {
	Stack s;
	method m;

	s = calloc(1, sizeof(struct _CBStack));
	assert(s);

	s->class = StackClass;
	s->llist = create_list();

	s->methods = create_list();
	m = mmethod("release", &release);
	push_back(s->methods, m);
	m = mmethod("push", &push);
	push_back(s->methods, m);
	m = mmethod("pop", &pop);
	push_back(s->methods, m);
	m = mmethod("peek", &peek);
	push_back(s->methods, m);

	s->parent = message(ObjectClass, "init");

	return s;
}

void *release(void *v, va_list *args) {
	Stack s = (Stack)v;
	message(s->parent, "release");
	free_list(s->methods, &free);
	free_list(s->llist, &message_release);
	free(s);
	return s;
}

void message_release(void *v) {
	message(v, "release");	
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