
#ifndef OBJECT_H
#define OBJECT_H

extern Class ObjectClass;

struct _Object {
	Class root;
	int retaincount;
};

void object_class_init();
Object object_init(void *v);

#endif
