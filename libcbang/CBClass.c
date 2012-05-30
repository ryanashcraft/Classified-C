
#include "CBang.h"

Class ClassClass = NULL;

static void *new(void *v, va_list *args);

void class_class_init() {
	method m;

	ClassClass = malloc(sizeof(struct _CBClass));
	assert(ClassClass);

	((Object)ClassClass)->root = ClassClass;
	((Object)ClassClass)->retaincount = 1;

	ClassClass->static_methods = create_list();
	m = mmethod("new", &new);
	push_back(ClassClass->static_methods, m);

	ClassClass->instance_methods = create_list();

	ClassClass->name = mstring("Class");
}

Class new_class(cstring name, Class parent_class) {
	Class c = cballoc(sizeof(struct _CBClass));
	object_init(c);
	((Object)c)->root = ClassClass;

	c->parent_class = parent_class;
	c->static_methods = create_list();
	c->instance_methods = create_list();
	c->name = mstring(name);

	return c;
}

void *new(void *v, va_list *args) {
	cstring name = va_arg(*args, cstring);
	Class parent_class = va_arg(*args, Class);

	return new_class(name, parent_class);
}
