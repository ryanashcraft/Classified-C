
#ifndef CB_CLASS_H
#define CB_CLASS_H

struct _CBClass {
	Class class;
	list *methods;
	string name;
	Class parent_class;
	spointer super;
};

extern Class ClassClass;

void class_class_init();

#endif
