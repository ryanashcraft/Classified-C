
#ifndef CB_OBJECT_H
#define CB_OBJECT_H

extern Class ObjectClass;

struct _CBObject {
	Class root;
	int retaincount;
};

void object_class_init();
Object object_init(void *v);

#endif
