
#define CLASS Thread
#define SUPER Object

#include "Classified-C.h"

proto(new);
proto(newWithTargetAndSelector);
proto(currentThread);
proto(joinAllThreads);
proto(run);
proto(join);
proto(isCurrentThread);
proto(addToAutoReleasePool);
proto(description);

void *msgWithStruct(void *arg);

static LinkedList threads;

defclass
	static(new);
	static(newWithTargetAndSelector);
	static(currentThread);
	static(joinAllThreads);

	instance(run);
	instance(join);
	instance(isCurrentThread);
	instance(addToAutoReleasePool);
	instance(description);

	threads = msg(LinkedListClass, "new");
end

defcon(new)
	self->thread = pthread_self();
	self->autoReleasePool = msg(LinkedListClass, "new");

	msg(threads, "pushBack", self);

	return self;
end

defcon(newWithTargetAndSelector)
	self->target = NEXT_ARG(Object);
	msg(self->target, "retain");
	self->selector = NEXT_ARG(cstring);
	self->thread = NULL;
	self->autoReleasePool = msg(LinkedListClass, "new");

	msg(threads, "pushBack", self);

	return self;
end

def(currentThread)
	Iterator iterator = msg(IteratorClass, "newWithLinkedList", threads);
	Thread element = NULL;
	Thread currentThread = NULL;
	while ( (element = msg(iterator, "next")) ) {
		if (msg(element, "isCurrentThread")) {
			currentThread = element;
			break;
		}
	}
	msg(iterator, "release");

	return currentThread;
end

def(joinAllThreads)
	Iterator iterator = msg(IteratorClass, "newWithLinkedList", threads);
	Thread element = NULL;
	while ( (element = msg(iterator, "next")) ) {
		msg(element, "join");
	}

	msg(iterator, "release");

	return self;
end

def(run)
	struct _message *message = malloc(sizeof(struct _message));
	message->target = self->target;
	message->selector = self->selector;
	assert(message);

	pthread_create(&self->thread, NULL, msgWithMessage, message);

	return self;
end

def(join)
	pthread_join(self->thread, NULL);

	return self;
end

def(isCurrentThread)
	if (self->thread == pthread_self()) {
		return YES;
	}

	return NO;
end

def(addToAutoReleasePool)
	msg(self->autoReleasePool, "pushBack", NEXT_ARG(Object));
	return self;
end

def(description)
	MutableString buffer = msg(MutableStringClass, "newWithCString", "");
	String part = msgSuper("description");
	msg(buffer, "concatenateWithString", part);
	msg(part, "release");

	part = msg(StringClass, "newWithFormatCString", " with pthread 0x%x", (size_t)self->thread);
	msg(buffer, "concatenateWithString", part);
	msg(part, "release");

	return buffer;
end
