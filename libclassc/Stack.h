
#ifndef STACK_H
#define STACK_H

extern Class StackClass;

typedef struct _Stack {
	struct _LinkedList base;
} *Stack;

void StackInit();

#endif
