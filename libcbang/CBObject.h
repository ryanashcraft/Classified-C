
#ifndef CB_OBJECT_H
#define CB_OBJECT_H

#define OBJECT_BASE Class class; list *methods; Object parent; int retaincount;

typedef struct _CBObject *Object;

struct _CBObject {
	OBJECT_BASE
};

extern Class ObjectClass;

void object_class_init();

#endif
