
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
	StackClass = message(ClassClass, "init", "Stack", ObjectClass);

	push_back(StackClass->methods, mmethod("init", &init));

	push_back(StackClass->instance_methods, mmethod("release", &release));
	push_back(StackClass->instance_methods, mmethod("push", &push));
	push_back(StackClass->instance_methods, mmethod("pop", &pop));
	push_back(StackClass->instance_methods, mmethod("peek", &peek));
}

void *init(void *v, va_list *args) {
	Stack o;

	o = calloc(1, sizeof(struct _CBStack));
	assert(o);

	o->class = StackClass;
	o->methods = StackClass->instance_methods;
	o->parent = message(ObjectClass, "init");
	o->retaincount = 1;

	o->llist = create_list();

	return o;
}

void *release(void *v, va_list *args) {
	Stack o = (Stack)v;
	--o->retaincount;
	message(o->parent, "release");

	if (o->retaincount == 0) {
		free_list(o->llist, &message_release);
		free(o);
		return NULL;
	}

	return o;
}

void message_release(void *v) {
	message(v, "release");	
}

void *push(void *v, va_list *args) {
	Stack o = (Stack)v;

	void *data = va_arg(*args, void *);
	push_front(o->llist, data);
	return NULL;
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