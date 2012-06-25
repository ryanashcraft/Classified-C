
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
proto(autorelease);
proto(finishAutoRelease);
proto(description);

void ObjectInit() {
	ObjectClass = new_class("Object", NULL);

	static(new);

	instance(init);
	instance(release);
	instance(dealloc);
	instance(retain);
	instance(autorelease);
	instance(finishAutoRelease);
	instance(description);
}

Object object_init(void *v) {
	Object self = (Object)v;

	self->retaincount = 1;
	self->autoreleased = NO;

	return self;
}

defcon(new)
	return self;
end

def(init)
	return object_init(v);
end

def(release)
	if (self->autoreleased) {
		self->autoreleased = NO;
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

def(autorelease)
	self->autoreleased = YES;
	msg(msg(ThreadClass, "currentThread"), "addToAutoReleasePool", self);
	--self->retaincount;

	return self;
end

def(finishAutoRelease)
	self->autoreleased = NO;
	return msg(self, "release");
end

def(description)
	return msg(msg(StringClass, "newWithFormatCString", "%s (%p)", self->root->name, v), "autorelease");
end
