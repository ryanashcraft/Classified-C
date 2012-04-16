
#ifndef CB_OBJECT_H
#define CB_OBJECT_H

typedef struct _CBObject *Object;

struct _CBObject {
	Class class;
	list *methods;
	Object parent;
};

extern Class ObjectClass;

void object_class_init();

#endif
