
#ifndef CB_STACK_H
#define CB_STACK_H

extern Class StackClass;

typedef struct _CBStack {
	Class class;
	list *llist;
	list *methods;
	struct _CBObject parent;
} *Stack;

void stack_class_init();

#endif
