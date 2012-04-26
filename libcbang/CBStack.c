
#include "CBang.h"
#include "CBStack.h"

Class StackClass = NULL;

typedef struct _CBStack {
	OBJECT_BASE
	
	list *llist;
} *Stack;

static void *init(void *v, va_list *args);

static void *dealloc(void *v, va_list *args);
static void *push(void *v, va_list *args);
static void *pop(void *v, va_list *args);
static void *peek(void *v, va_list *args);

void message_release(void *v);

void stack_class_init() {
	StackClass = msg(ClassClass, "init", "Stack", ObjectClass);

	// Define class methods
	push_back(StackClass->methods, mmethod("init", &init));

	// Define instance methods
	push_back(StackClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(StackClass->instance_methods, mmethod("push", &push));
	push_back(StackClass->instance_methods, mmethod("pop", &pop));
	push_back(StackClass->instance_methods, mmethod("peek", &peek));
}

void *init(void *v, va_list *args) {
	Stack o;

	o = calloc(1, sizeof(struct _CBStack));
	assert(o);

	Object root = va_arg(*args, Object);
	if (!root) {
		root = (Object)o;
	}

	o->class = StackClass;
	o->methods = StackClass->instance_methods;
	o->parent = msg(ObjectClass, "init", root);
	o->root = root;

	o->llist = create_list();

	return o;
}

void *dealloc(void *v, va_list *args) {
	Stack o = (Stack)v;
	msg(o->parent, "dealloc");
	free_list(o->llist, &message_release);
	free(o);
	return NULL;
}

void message_release(void *v) {
	msg(v, "release");	
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