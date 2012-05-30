
#ifndef CLASS_H
#define CLASS_H

struct _Class {
	struct _Object base;
	Class parent_class;
	list *static_methods;
	list *instance_methods;
	cstring name;
};

extern Class ClassClass;

void class_class_init();
Class new_class(cstring name, Class parent_class);

#endif
