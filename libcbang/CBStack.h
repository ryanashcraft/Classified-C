
#ifndef CB_STACK_H
#define CB_STACK_H

extern Class StackClass;

typedef struct _CBStack {
	Class class;
	list *methods;
	Object parent;
	list *llist;
} *Stack;

void stack_class_init();

#endif
