
#ifndef CB_ARRAY_H
#define CB_ARRAY_H

extern Class ArrayClass;

typedef struct _CBArray {
	struct _CBObject base;
	Object *value;
	int capacity;
} *Array;

void array_class_init();

#endif
