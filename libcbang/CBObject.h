
#ifndef CB_OBJECT_H
#define CB_OBJECT_H

#define OBJECT_BASE Class class; list *methods; Object parent; Object root;

typedef struct _CBObject *Object;

struct _CBObject {
	OBJECT_BASE

	int retaincount;
};

extern Class ObjectClass;

void object_class_init();

#endif
