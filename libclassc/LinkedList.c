
#include "../libclassc/Classified-C.h"
#include "LinkedList.h"

IMPLEMENTATION(LinkedListClass);

PROTOTYPE(new);
PROTOTYPE(init);
PROTOTYPE(dealloc);
PROTOTYPE(description);

void call_method(void *v, va_list *args);

void linked_list_class_init() {
	LinkedListClass = msg(ClassClass, "new", "LinkedList", ObjectClass);

	REGISTER_CLASS_METHOD(LinkedListClass, "new", new);

	REGISTER_METHOD(LinkedListClass, "init", init);
	REGISTER_METHOD(LinkedListClass, "dealloc", dealloc);
	REGISTER_METHOD(LinkedListClass, "description", description);
}

DEFINE(new) {
	NEW(LinkedListClass, struct _LinkedList);

	init(self, args);

	return self;
}

DEFINE(init) {
	CONTEXT(LinkedList);

	self->value = create_list();

	return self;
}

DEFINE(dealloc) {
	CONTEXT(LinkedList);

	free_list(self->value, &msg_release);

	return msg_cast(ObjectClass, self, "dealloc");
}

DEFINE(description) {
	CONTEXT(LinkedList);

	return msg(StringClass, "newWithFormatCString", "%s", "[LinkedList]");
}

DEFINE(pushFront) {
	CONTEXT(LinkedList);

	push_front(self->value, NEXT_ARG(void *));

	return self;
}

DEFINE(pushBack) {
	CONTEXT(LinkedList);

	push_back(self->value, NEXT_ARG(void *));

	return self;
}

DEFINE(removeFront) {
	CONTEXT(LinkedList);

	remove_front(self->value, &msg_release);

	return self;
}

DEFINE(removeBack) {
	CONTEXT(LinkedList);

	remove_back(self->value, &msg_release);

	return self;
}

DEFINE(front) {
	CONTEXT(LinkedList);

	return ll_front(self->value);
}

DEFINE(back) {
	CONTEXT(LinkedList);

	return ll_back(self->value);
}

DEFINE(performOnEach) {
	CONTEXT(LinkedList);

	cstring method_name = NEXT_ARG(cstring);

	traverse_with_args(self->value, call_method, method_name);

	return self;
}

void call_method(void *v, va_list *args) {
	cstring method_name = va_arg(*args, cstring);

	msg(v, method_name);
}
