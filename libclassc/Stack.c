
#include "Classified-C.h"

IMPLEMENTATION(StackClass);

PROTOTYPE(new);
PROTOTYPE(init);
PROTOTYPE(dealloc);
PROTOTYPE(push);
PROTOTYPE(pop);
PROTOTYPE(peek);

void message_release(void *v);

void stack_class_init() {
	StackClass = msg(ClassClass, "new", "Stack", ObjectClass);

	REGISTER_CLASS_METHOD(StackClass, "new", new);

	REGISTER_METHOD(StackClass, "init", init);
	REGISTER_METHOD(StackClass, "dealloc", dealloc);
	REGISTER_METHOD(StackClass, "push", push);
	REGISTER_METHOD(StackClass, "pop", pop);
	REGISTER_METHOD(StackClass, "peek", peek);
}

DEFINE(new) {
	NEW(StackClass, struct _Stack);

	init(self, args);

	return self;
}

DEFINE(init) {
	Stack self = (Stack)v;

	self->llist = create_list();

	return self;
}

DEFINE(dealloc) {
	Stack self = (Stack)v;

	free_list(self->llist, &message_release);

	return msg_cast(ObjectClass, self, "dealloc");
}

DEFINE(push) {
	Stack self = (Stack)v;

	void *data = NEXT_ARG(void *);
	push_front(self->llist, data);

	return self;
}

DEFINE(pop) {
	Stack self = (Stack)v;

	if (is_empty(self->llist)) {
		return NULL;
	}

	void *retval = peek(self, NULL);
	remove_front(self->llist, &message_release);

	return retval;
}

DEFINE(peek) {
	Stack self = (Stack)v;

	if (is_empty(self->llist)) {
		return NULL;
	}

	return front(self->llist);
}

void message_release(void *v) {
	msg(v, "release");	
}
