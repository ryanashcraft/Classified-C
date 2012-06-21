
#include "Classified-C.h"

#define TABLE_START_MAX_SIZE 16
#define TABLE_START_RATIO 2

IMPLEMENTATION(ClassClass);

PROTOTYPE(new);

void class_class_init() {
	ClassClass = malloc(sizeof(struct _Class));
	assert(ClassClass);

	((Object)ClassClass)->root = ClassClass;
	((Object)ClassClass)->retaincount = 1;

	ClassClass->static_methods = ht_create(4, 2);
	REGISTER_CLASS_METHOD(ClassClass, "new", new);

	ClassClass->instance_methods = ht_create(4, 2);

	ClassClass->name = mstring("Class");
}

Class new_class(cstring name, Class parent_class) {
	NEW(ClassClass, struct _Class);

	self->parent_class = parent_class;
	self->static_methods = ht_create(TABLE_START_MAX_SIZE, TABLE_START_RATIO);
	self->instance_methods = ht_create(TABLE_START_MAX_SIZE, TABLE_START_RATIO);
	self->name = mstring(name);

	return self;
}

DEFINE(new) {
	cstring name = NEXT_ARG(cstring);
	Class parent_class = NEXT_ARG(Class);

	return new_class(name, parent_class);
}
