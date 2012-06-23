
#define CLASS Stack
#define SUPER Object

#include "Classified-C.h"

proto(new);
proto(init);
proto(dealloc);
proto(push);
proto(pop);
proto(peek);
proto(isEmpty);

defclass
	static(new);

	instance(init);
	instance(dealloc);
	instance(push);
	instance(pop);
	instance(peek);
	instance(isEmpty);
end

defcon(new)
	init(self, args);

	return self;
end

def(init)
	self->llist = create_list();

	return self;
end

def(dealloc)
	free_list(self->llist, &msg_release);

	return msgSuper("dealloc");
end

def(push)
	Object o = NEXT_ARG(Object);
	push_front(self->llist, o);
	msg(o, "retain");

	return self;
end

def(pop)
	if (is_empty(self->llist)) {
		return NULL;
	}

	void *retval = peek(self, NULL);
	remove_front(self->llist, &msg_release);

	return retval;
end

def(peek)
	if (is_empty(self->llist)) {
		return NULL;
	}

	return ll_front(self->llist);
end

def(isEmpty)
	if (is_empty(self->llist)) {
		return YES;
	}

	return NO;
end
