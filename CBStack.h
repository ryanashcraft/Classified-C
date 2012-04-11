
#ifndef CB_STACK_H
#define CB_STACK_H

typedef struct _CBStack {
	struct _obj meta;
	list *llist;
} *CBStack;

class cbstack_init();

#endif