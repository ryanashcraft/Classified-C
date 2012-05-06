
#ifndef CB_CLASS_H
#define CB_CLASS_H

struct _CBClass {
	struct _CBObject base;
	Class parent_class;
	list *static_methods;
	list *instance_methods;
	string name;
};

extern Class ClassClass;

void class_class_init();
Class new_class(string name, Class parent_class);

#endif
