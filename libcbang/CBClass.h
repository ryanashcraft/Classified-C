
#ifndef CB_CLASS_H
#define CB_CLASS_H

struct _CBClass {
	Class class;
	list *methods;
	Class parent;
	list *instance_methods;
	string name;
};

extern Class ClassClass;

void class_class_init();

#endif
