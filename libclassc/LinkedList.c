
#define CLASS LinkedList
#define SUPER Object

#include "Classified-C.h"

proto(new);
proto(init);
proto(dealloc);
proto(length);
proto(pushFront);
proto(pushBack);
proto(removeFront);
proto(removeBack);
proto(removeObject);
proto(getFront);
proto(getBack);
proto(get);
proto(performOnEach);
proto(clear);
proto(contains);

int msg_is_equal(const void *a, const void *b);
void msg_with_string(void *v, va_list *args);

proto(getFirst);

defclass
	constructor(new);

	instance(init);
	instance(dealloc);
	instance(length);
	instance(pushFront);
	instance(pushBack);
	instance(removeFront);
	instance(removeBack);
	instance(removeObject);
	instance(getFront);
	instance(getBack);
	instance(get);
	instance(performOnEach);
	instance(clear);
	instance(contains);
	instance(getFirst);
end

defcon(new)
	init(self, args);

	return self;
end

def(init)
	self->value = create_list();

	return self;
end

def(dealloc)
	free_list(self->value, &msg_release);

	return msgSuper("dealloc");
end

def(length)
	return msg(msg(IntegerClass, "newWithInt", self->value->size), "autoRelease");
end

def(pushFront)
	Object o = nextArg(Object);
	push_front(self->value, o);
	msg(o, "retain");

	return self;
end

def(pushBack)
	Object o = nextArg(Object);
	push_back(self->value, o);
	msg(o, "retain");

	return self;
end

def(removeFront)
	Object retVal = msg(self, "getFront");
	remove_front(self->value, &msg_release);

	return retVal;
end

def(removeBack)
	Object retVal = msg(self, "getBack");
	remove_back(self->value, &msg_release);

	return retVal;
end

def(removeObject)
	Object o = nextArg(Object);
	remove_data(self->value, o, same_pointer, &msg_release);

	return NULL;
end

def(getFront)
	return ll_front(self->value);
end

def(getBack)
	return ll_back(self->value);
end

def(get)
	return ll_get_index(self->value, nextArg(int));
end

def(performOnEach)
	cstring method_name = nextArg(cstring);

	traverse_with_args(self->value, &msg_with_string, method_name);

	return self;
end

def(clear)
	empty_list(self->value, &msg_release);

	return self;
end

def(contains)
	if (find_occurrence(self->value, nextArg(Object), &msg_is_equal)) {
		return YES;
	}

	return NO;
end

int msg_is_equal(const void *a, const void *b) {
	return (size_t)msg((Object)a, "equals", b);
}

void msg_with_string(void *v, va_list *args) {
	cstring method_name = va_arg(*args, cstring);
	msg(v, method_name, args);
}

def(getFirst)
	cstring method_name = nextArg(cstring);

	return get_first_occurrence(self->value, &test_by_calling_method, method_name);
end
