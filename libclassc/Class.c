
#include "Classified-C.h"

IMPLEMENTATION(ClassClass);

PROTOTYPE(new);

void class_class_init() {
	ClassClass = malloc(sizeof(struct _Class));
	assert(ClassClass);

	((Object)ClassClass)->root = ClassClass;
	((Object)ClassClass)->retaincount = 1;

	ClassClass->static_methods = create_list();
	REGISTER_CLASS_METHOD(ClassClass, "new", new);

	ClassClass->instance_methods = create_list();

	ClassClass->name = mstring("Class");
}

Class new_class(cstring name, Class parent_class) {
	NEW(ClassClass, struct _Class);

	self->parent_class = parent_class;
	self->static_methods = create_list();
	self->instance_methods = create_list();
	self->name = mstring(name);

	return self;
}

DEFINE(new) {
	cstring name = NEXT_ARG(cstring);
	Class parent_class = NEXT_ARG(Class);

	return new_class(name, parent_class);
}
