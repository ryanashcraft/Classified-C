
#define CLASS Thread
#define SUPER Object

#include "Classified-C.h"
#include "Stack.h"

proto(new);
proto(newWithTargetAndSelectorAndUserData);
proto(currentThread);
proto(joinAllThreads);
proto(run);
proto(join);
proto(isCurrentThread);
proto(pushAutoReleasePool);
proto(releaseTopAutoReleasePool);
proto(addToAutoReleasePool);
proto(description);

void *msgWithStruct(void *arg);

static LinkedList threads;

defclass
	static(new);
	static(newWithTargetAndSelectorAndUserData);
	static(currentThread);
	static(joinAllThreads);

	instance(run);
	instance(join);
	instance(isCurrentThread);
	instance(pushAutoReleasePool);
	instance(releaseTopAutoReleasePool);
	instance(addToAutoReleasePool);
	instance(description);

	threads = msg(LinkedListClass, "new");
end

defcon(new)
	self->thread = pthread_self();
	self->autoReleasePools = msg(StackClass, "new");

	AutoReleasePool pool = msg(AutoReleasePoolClass, "new");
	msg(self, "pushAutoReleasePool", pool);

	msg(threads, "pushBack", self);

	return self;
end

defcon(newWithTargetAndSelectorAndUserData)
	self->target = NEXT_ARG(Object);
	msg(self->target, "retain");
	self->selector = mstring(NEXT_ARG(cstring));
	self->userData = NEXT_ARG(LinkedList);
	msg(self->userData, "retain");

	self->thread = NULL;
	self->autoReleasePools = msg(StackClass, "new");

	AutoReleasePool pool = msg(AutoReleasePoolClass, "new");
	msg(self, "pushAutoReleasePool", pool);

	msg(threads, "pushBack", self);

	return self;
end

def(currentThread)
	return current_thread();
end

def(joinAllThreads)
	msg(threads, "performOnEach", "join");

	msg(threads, "performOnEach", "releaseTopAutoReleasePool");

	return self;
end

def(run)
	struct _message *message = malloc(sizeof(struct _message));
	message->target = self->target;
	message->selector = self->selector;
	message->userData = self->userData;
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

def(pushAutoReleasePool)
	AutoReleasePool pool = NEXT_ARG(AutoReleasePool);
	msg(self->autoReleasePools, "push", pool);

	return self;
end

def(releaseTopAutoReleasePool)
	msg(msg(self->autoReleasePools, "peek"), "release");

	return self;
end

def(addToAutoReleasePool)
	Object o = NEXT_ARG(Object);
	msg(msg(self->autoReleasePools, "peek"), "push", o);

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

Thread current_thread() {
	Thread thread = msg(threads, "getFirst", "isCurrentThread");

	return thread;
}
