
#include "../libclassc/Classified-C.h"
#include "LinkedList.h"

IMPLEMENTATION(LinkedListClass);

PROTOTYPE(new);
PROTOTYPE(init);
PROTOTYPE(dealloc);
PROTOTYPE(description);
PROTOTYPE(pushFront);
PROTOTYPE(pushBack);
PROTOTYPE(removeFront);
PROTOTYPE(removeBack);
PROTOTYPE(getFront);
PROTOTYPE(getBack);
PROTOTYPE(performOnEach);

void call_method(void *v, va_list *args);

void linked_list_class_init() {
	LinkedListClass = msg(ClassClass, "new", "LinkedList", ObjectClass);

	REGISTER_CLASS_METHOD(LinkedListClass, "new", new);

	REGISTER_METHOD(LinkedListClass, "init", init);
	REGISTER_METHOD(LinkedListClass, "dealloc", dealloc);
	REGISTER_METHOD(LinkedListClass, "description", description);
	REGISTER_METHOD(LinkedListClass, "pushFront", pushFront);
	REGISTER_METHOD(LinkedListClass, "pushBack", pushBack);
	REGISTER_METHOD(LinkedListClass, "removeFront", removeFront);
	REGISTER_METHOD(LinkedListClass, "removeBack", removeBack);
	REGISTER_METHOD(LinkedListClass, "getFront", getFront);
	REGISTER_METHOD(LinkedListClass, "getBack", getBack);
	REGISTER_METHOD(LinkedListClass, "performOnEach", performOnEach);
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

	Object o = NEXT_ARG(Object);
	push_front(self->value, o);
	msg(o, "retain");

	return self;
}

DEFINE(pushBack) {
	CONTEXT(LinkedList);

	Object o = NEXT_ARG(Object);
	push_back(self->value, o);
	msg(o, "retain");

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

DEFINE(getFront) {
	CONTEXT(LinkedList);

	return ll_front(self->value);
}

DEFINE(getBack) {
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
