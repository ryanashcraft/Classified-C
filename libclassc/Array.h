
#ifndef ARRAY_H
#define ARRAY_H

extern Class ArrayClass;

typedef struct _Array {
	struct _Object base;
	Object *value;
	int capacity;
	int length;
} *Array;

void ArrayInit();

#endif
