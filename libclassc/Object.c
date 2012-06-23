
#include "Classified-C.h"

Class ObjectClass = NULL;

#define TYPE Object
#define SUPER NULL

proto(new)
proto(init)
proto(release)
proto(dealloc)
proto(retain)
proto(description)

void ObjectInit() {
	ObjectClass = new_class("Object", NULL);

	registerStatic("new", new);

	register("init", init);
	register("release", release);
	register("dealloc", dealloc);
	register("retain", retain);
	register("description", description);
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

def(description)
	return msg(StringClass, "newWithFormatCString", "%s (%p)", self->root->name, v);
end
