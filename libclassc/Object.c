
#include "Classified-C.h"

IMPLEMENTATION(ObjectClass);

PROTOTYPE(new);
PROTOTYPE(init);
PROTOTYPE(release);
PROTOTYPE(dealloc);
PROTOTYPE(retain);
PROTOTYPE(description);

void object_class_init() {
	ObjectClass = new_class("Object", NULL);

	REGISTER_CLASS_METHOD(ObjectClass, "new", new);

	REGISTER_METHOD(ObjectClass, "init", init);
	REGISTER_METHOD(ObjectClass, "release", release);
	REGISTER_METHOD(ObjectClass, "dealloc", dealloc);
	REGISTER_METHOD(ObjectClass, "retain", retain);
	REGISTER_METHOD(ObjectClass, "description", description);
}

Object object_init(void *v) {
	Object self = (Object)v;

	self->retaincount = 1;

	return self;
}

DEFINE(new) {
	NEW(ObjectClass, struct _Object);

	return self;
}

DEFINE(init) {
	return object_init(v);
}

DEFINE(release) {
	CONTEXT(Object);

	--self->retaincount;

	if (self->retaincount == 0) {
		return msg(self, "dealloc");
	}

	return self;
}

DEFINE(dealloc) {
	CONTEXT(Object);
	
	free(self);

	return NULL;
}

DEFINE(retain) {
	CONTEXT(Object);

	self->retaincount++;

	return self;
}

DEFINE(description) {
	CONTEXT(Object);

	return msg(StringClass, "newWithFormatCString", "%s (%p)", self->root->name, v);
}
