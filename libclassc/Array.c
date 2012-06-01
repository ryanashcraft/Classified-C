
#include "Classified-C.h"

IMPLEMENTATION(ArrayClass);

PROTOTYPE(newWithObjects);
PROTOTYPE(initWithObjects);
PROTOTYPE(dealloc);
PROTOTYPE(performMethodOnEach);
PROTOTYPE(get);
PROTOTYPE(length);

void array_class_init() {
	ArrayClass = msg(ClassClass, "new", "Array", ObjectClass);

	REGISTER_CLASS_METHOD(ArrayClass, "newWithObjects", newWithObjects);

	REGISTER_METHOD(ArrayClass, "initWithObjects", initWithObjects);
	REGISTER_METHOD(ArrayClass, "dealloc", dealloc);
	REGISTER_METHOD(ArrayClass, "performMethodOnEach", performMethodOnEach);
	REGISTER_METHOD(ArrayClass, "get", get);
	REGISTER_METHOD(ArrayClass, "length", length);
}

DEFINE(newWithObjects) {
	NEW(ArrayClass, struct _Array);

	initWithObjects(self, args);

	return self;
}

DEFINE(initWithObjects) {
	CONTEXT(Array);
	
	self->capacity = 0;
	self->length = 0;

	Object element = NULL;
	va_list duplicate_arg_list;
	va_copy(duplicate_arg_list, *ARGS);
	while ((element = va_arg(duplicate_arg_list, Object)) != NULL) {
		self->capacity++;
	}
	self->capacity++; /* for NULL terminator */

	self->value = calloc(self->capacity, sizeof(Object));
	assert(self->value);
	int i;
	for (i = 0; (element = NEXT_ARG(Object)) != NULL; i++) {
		self->value[i] = element;
		msg(element, "retain");
		self->length++;
	}

	return self;
}

DEFINE(dealloc) {
	CONTEXT(Array);

	Object element = NULL;
	int i;
	for (i = 0; (element = self->value[i]) != NULL; i++) {
		msg(element, "release");
	}

	free(self->value);

	return msg_cast(ObjectClass, self, "dealloc");
}

DEFINE(performMethodOnEach) {
	CONTEXT(Array);

	cstring method_name = NEXT_ARG(cstring);
	Object element = NULL;
	int i;
	for (i = 0; (element = self->value[i]) != NULL; i++) {
		msg(element, method_name);
	}

	return self;
}

DEFINE(get) {
	CONTEXT(Array);

	int index = NEXT_ARG(int);
	Object obj = self->value[index];

	return obj;
}

DEFINE(length) {
	CONTEXT(Array);

	return msg(IntegerClass, "newWithInt", self->length);
}
