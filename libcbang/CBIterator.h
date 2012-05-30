
#ifndef CB_ITERATOR_H
#define CB_ITERATOR_H

extern Class IteratorClass;

typedef struct _CBIterator {
	struct _CBObject base;
	Array elements;
	int nextPointer;
} *Iterator;

void iterator_class_init();

#endif
