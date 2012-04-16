
#ifndef CB_STACK_H
#define CB_STACK_H

extern Class StackClass;

typedef struct _CBStack {
	OBJECT_BASE
	
	list *llist;
} *Stack;

void stack_class_init();

#endif
