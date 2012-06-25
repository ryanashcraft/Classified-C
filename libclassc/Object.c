
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
proto(description);

void ObjectInit() {
	ObjectClass = new_class("Object", NULL);

	static(new);

	instance(init);
	instance(release);
	instance(dealloc);
	instance(retain);
	instance(autorelease);
	instance(description);
}

Object object_init(void *v) {
	Object self = (Object)v;

	self->retaincount = 1;

	return self;
}

defcon(new)
	return self;
end

def(init)
	return object_init(v);
end

def(release)
	--self->retaincount;

	if (self->retaincount == 0) {
		return msg(self, "dealloc");
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
	msg(msg(ThreadClass, "currentThread"), "addToAutoReleasePool", self);

	return self;
end

def(description)
	return msg(StringClass, "newWithFormatCString", "%s (%p)", self->root->name, v);
end
