
#ifndef CB_CLASS_H
#define CB_CLASS_H

struct _CBClass {
	OBJECT_BASE

	list *instance_methods;
	string name;
	Class parent_class;
};

extern Class ClassClass;

void class_class_init();

#endif
