
#ifndef ITERATOR_H
#define ITERATOR_H

extern Class IteratorClass;

typedef struct _Iterator {
	struct _Object base;
	Array elements;
	int nextPointer;
} *Iterator;

void iterator_class_init();

#endif
