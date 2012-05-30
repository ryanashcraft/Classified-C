
#include "Classified-C.h"

Class StackClass = NULL;

static void *new(void *v, va_list *args);

static void *init(void *v, va_list *args);
static void *dealloc(void *v, va_list *args);
static void *push(void *v, va_list *args);
static void *pop(void *v, va_list *args);
static void *peek(void *v, va_list *args);

void message_release(void *v);

void stack_class_init() {
	StackClass = msg(ClassClass, "new", "Stack", ObjectClass);

	push_back(StackClass->static_methods, mmethod("new", &new));

	push_back(StackClass->instance_methods, mmethod("init", &init));
	push_back(StackClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(StackClass->instance_methods, mmethod("push", &push));
	push_back(StackClass->instance_methods, mmethod("pop", &pop));
	push_back(StackClass->instance_methods, mmethod("peek", &peek));
}

void *new(void *v, va_list *args) {
	Stack o = cc_alloc(sizeof(struct _Stack));
	init(o, args);
	((Object)o)->root = StackClass;
	return o;
}

void *init(void *v, va_list *args) {
	Stack o = (Stack)v;
	msg_cast(ObjectClass, o, "init");
	o->llist = create_list();
	return o;
}

void *dealloc(void *v, va_list *args) {
	Stack o = (Stack)v;
	free_list(o->llist, &message_release);
	return msg_cast(ObjectClass, o, "dealloc");
}

void *push(void *v, va_list *args) {
	Stack o = (Stack)v;

	void *data = va_arg(*args, void *);
	push_front(o->llist, data);
	return o;
}

void *pop(void *v, va_list *args) {
	Stack o = (Stack)v;

	if (is_empty(o->llist)) {
		return NULL;
	}

	void *retval = peek(o, NULL);
	remove_front(o->llist, &message_release);
	return retval;
}

void *peek(void *v, va_list *args) {
	Stack o = (Stack)v;

	if (is_empty(o->llist)) {
		return NULL;
	}

	return front(o->llist);
}

void message_release(void *v) {
	msg(v, "release");	
}
