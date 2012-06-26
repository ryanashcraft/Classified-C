
#define CLASS Class
#define SUPER Object

#include "Classified-C.h"

Class ClassClass = NULL;

#define TABLE_START_MAX_SIZE 16
#define TABLE_START_RATIO 2

proto(new);

void ClassInit() {
	ClassClass = malloc(sizeof(struct _Class));
	assert(ClassClass);

	((Object)ClassClass)->root = ClassClass;
	((Object)ClassClass)->retaincount = 1;

	ClassClass->static_methods = ht_create(4, 2);
	static(new);

	ClassClass->instance_methods = ht_create(4, 2);

	ClassClass->name = mstring("Class");
}

Class new_class(cstring name, Class parent_class) {
	STRUCT *self = cc_alloc(sizeof(STRUCT));
	object_init(self);
	((Object)self)->root = ClassClass;

	self->parent_class = parent_class;
	self->static_methods = ht_create(TABLE_START_MAX_SIZE, TABLE_START_RATIO);
	self->instance_methods = ht_create(TABLE_START_MAX_SIZE, TABLE_START_RATIO);
	self->name = mstring(name);

	return self;
}

def(new)
	cstring name = nextArg(cstring);
	Class parent_class = nextArg(Class);

	return new_class(name, parent_class);
end
