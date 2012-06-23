
#ifndef STACK_H
#define STACK_H

extern Class StackClass;

typedef struct _Stack {
	struct _Object base;
	list *llist;
} *Stack;

void StackInit();

#endif
