
#ifndef CLASS_H
#define CLASS_H

struct _Class {
	struct _Object base;
	Class parent_class;
	hashtable *static_methods;
	hashtable *instance_methods;
	cstring name;
};

extern Class ClassClass;

void ClassInit();
Class new_class(cstring name, Class parent_class);

#endif
