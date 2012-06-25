
#define CLASS Object
#define SUPER_CLASS_REF NULL

#include "Classified-C.h"
#include "Thread.h"

Class ObjectClass = NULL;

proto(new);
proto(init);
proto(release);
proto(dealloc);
proto(retain);
proto(autoRelease);
proto(finishAutoRelease);
proto(description);

void ObjectInit() {
	ObjectClass = new_class("Object", NULL);

	static(new);

	instance(init);
	instance(release);
	instance(dealloc);
	instance(retain);
	instance(autoRelease);
	instance(finishAutoRelease);
	instance(description);
}

Object object_init(void *v) {
	Object self = (Object)v;

	self->retaincount = 1;
	self->autoReleased = NO;

	return self;
}

defcon(new)
	return self;
end

def(init)
	return object_init(v);
end

def(release)
	if (self->autoReleased) {
		self->autoReleased = NO;
		msg(msg(ThreadClass, "currentThread"), "removeFromAutoReleasePool", self);
	} else {
		--self->retaincount;

		if (self->retaincount == 0) {
			return msg(self, "dealloc");
		}
	}

	return self;
end

def(dealloc)	
	free(self);

	return NULL;
end

def(retain)
	self->retaincount++;

	return self;
end

def(autoRelease)
	self->autoReleased = YES;
	msg(msg(ThreadClass, "currentThread"), "addToAutoReleasePool", self);
	--self->retaincount;

	return self;
end

def(finishAutoRelease)
	self->autoReleased = NO;
	return msg(self, "release");
end

def(description)
	return msg(msg(StringClass, "newWithFormatCString", "%s (%p)", self->root->name, v), "autoRelease");
end
