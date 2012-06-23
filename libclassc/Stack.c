
#define TYPE Stack
#define SUPER Object

#include "Classified-C.h"

proto(new);
proto(init);
proto(dealloc);
proto(push);
proto(pop);
proto(peek);

defclass
	static(new);

	instance(init);
	instance(dealloc);
	instance(push);
	instance(pop);
	instance(peek);
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

	return msg_cast(ObjectClass, self, "dealloc");
end

def(push)
	void *data = NEXT_ARG(void *);
	push_front(self->llist, data);

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
