
#ifndef CB_STACK_H
#define CB_STACK_H

typedef struct _cbstack_data *cbstack_data;

struct _cbstack_data {
	list *llist;
};

class cbstack_init();

#endif