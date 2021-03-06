
#ifndef ITERATOR_H
#define ITERATOR_H

extern Class IteratorClass;

typedef struct _Iterator {
	struct _Object base;
	Object elements;
	int nextPointer;
} *Iterator;

void IteratorInit();

#endif
