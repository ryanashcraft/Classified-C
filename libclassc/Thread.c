
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
proto(pushNewAutoReleasePool);
proto(popAutoReleasePool);
proto(addToAutoReleasePool);
proto(removeFromAutoReleasePool);
proto(description);

void *msgWithStruct(void *arg);

static LinkedList threads;

defclass {
	constructor(new);
	constructor(newWithTargetAndSelectorAndUserData);

	static(currentThread);
	static(joinAllThreads);

	instance(run);
	instance(join);
	instance(isCurrentThread);
	instance(pushNewAutoReleasePool);
	instance(popAutoReleasePool);
	instance(addToAutoReleasePool);
	instance(removeFromAutoReleasePool);
	instance(description);

	threads = msg(LinkedListClass, "new");
} end

defcon(new) {
	self->thread = pthread_self();
	self->autoReleasePools = msg(StackClass, "new");

	msg(self, "pushNewAutoReleasePool");

	msg(threads, "pushBack", self);

	return self;
} end

defcon(newWithTargetAndSelectorAndUserData) {
	self->target = nextArg(Object);
	msg(self->target, "retain");
	self->selector = mstring(nextArg(cstring));
	self->userData = nextArg(LinkedList);
	msg(self->userData, "retain");

	self->thread = NULL;
	self->autoReleasePools = msg(StackClass, "new");

	msg(self, "pushNewAutoReleasePool");

	msg(threads, "pushBack", self);

	return self;
} end

defstat(currentThread) {
	return current_thread();
} end

defstat(joinAllThreads) {
	msg(threads, "performOnEach", "join");

	msg(threads, "performOnEach", "popAutoReleasePool");

	return self;
} end

def(run) {
	struct _message *message = malloc(sizeof(struct _message));
	message->target = self->target;
	message->selector = self->selector;
	message->userData = self->userData;
	assert(message);

	pthread_create(&self->thread, NULL, msgWithMessage, message);

	return self;
} end

def(join) {
	pthread_join(self->thread, NULL);

	return self;
} end

def(isCurrentThread) {
	if (self->thread == pthread_self()) {
		return YES;
	}

	return NO;
} end

def(pushNewAutoReleasePool) {
	AutoReleasePool pool = msg(AutoReleasePoolClass, "new");
	msg(self->autoReleasePools, "push", pool);

	return self;
} end

def(popAutoReleasePool) {
	AutoReleasePool pool = msg(self->autoReleasePools, "pop");
	msg(pool, "release");

	return self;
} end

def(addToAutoReleasePool) {
	Object o = nextArg(Object);
	msg(msg(self->autoReleasePools, "peek"), "push", o);

	return self;
} end

def(removeFromAutoReleasePool) {
	Object o = nextArg(Object);
	AutoReleasePool pool = msg(self->autoReleasePools, "peek");
	assert(pool);
	msg(pool, "removeObject", o);

	return self;
} end

def(description) {
	MutableString buffer = msg(MutableStringClass, "newWithCString", "");
	String part = msgSuper("description");
	msg(buffer, "concatenateWithString", part);
	msg(part, "release");

	part = msg(StringClass, "newWithFormatCString", " with pthread 0x%x", (size_t)self->thread);
	msg(buffer, "concatenateWithString", part);
	msg(part, "release");

	return msg(buffer, "autoRelease");
} end

Thread current_thread() {
	Thread thread = msg(threads, "getFirst", "isCurrentThread");

	return thread;
}
