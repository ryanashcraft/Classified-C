
#define CLASS Array
#define SUPER Object

#include "Classified-C.h"

proto(newWithObjects);
proto(initWithObjects);
proto(dealloc);
proto(performOnEach);
proto(get);
proto(length);

defclass {
	constructor(newWithObjects);

	instance(initWithObjects);
	instance(dealloc);
	instance(performOnEach);
	instance(get);
	instance(length);
} end

defcon(newWithObjects) {
	initWithObjects(self, args);

	return self;
} end

def(initWithObjects) {	
	self->capacity = 0;
	self->length = 0;

	Object element = NULL;
	va_list duplicate_arg_list;
	va_copy(duplicate_arg_list, *args);
	while ((element = va_arg(duplicate_arg_list, Object)) != NULL) {
		self->capacity++;
	}
	self->capacity++; /* for NULL terminator */

	self->value = calloc(self->capacity, sizeof(Object));
	assert(self->value);
	int i;
	for (i = 0; (element = nextArg(Object)) != NULL; i++) {
		self->value[i] = element;
		msg(element, "retain");
		self->length++;
	}

	return self;
} end

def(dealloc) {
	Object element = NULL;
	int i;
	for (i = 0; (element = self->value[i]) != NULL; i++) {
		msg(element, "release");
	}

	free(self->value);

	return msgSuper("dealloc");
} end

def(performOnEach) {
	cstring method_name = nextArg(cstring);
	Object element = NULL;
	int i;
	for (i = 0; (element = self->value[i]) != NULL; i++) {
		msg(element, method_name);
	}

	return self;
} end

def(get) {
	int index = nextArg(int);
	Object obj = self->value[index];

	return obj;
} end

def(length) {
	return msg(IntegerClass, "newWithInt", self->length);
} end
