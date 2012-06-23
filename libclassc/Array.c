
#include "Classified-C.h"

#define TYPE Array
#define SUPER ObjectClass

proto(newWithObjects);
proto(initWithObjects);
proto(dealloc);
proto(performOnEach);
proto(get);
proto(length);

defclass
	ArrayClass = msg(ClassClass, "new", "Array", ObjectClass);

	static(newWithObjects);

	instance(initWithObjects);
	instance(dealloc);
	instance(performOnEach);
	instance(get);
	instance(length);
end

defcon(newWithObjects)
	initWithObjects(self, args);

	return self;
end

def(initWithObjects)	
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
end

def(dealloc)
	Object element = NULL;
	int i;
	for (i = 0; (element = self->value[i]) != NULL; i++) {
		msg(element, "release");
	}

	free(self->value);

	return msg_cast(ObjectClass, self, "dealloc");
end

def(performOnEach)
	cstring method_name = NEXT_ARG(cstring);
	Object element = NULL;
	int i;
	for (i = 0; (element = self->value[i]) != NULL; i++) {
		msg(element, method_name);
	}

	return self;
end

def(get)
	int index = NEXT_ARG(int);
	Object obj = self->value[index];

	return obj;
end

def(length)
	return msg(IntegerClass, "newWithInt", self->length);
end
