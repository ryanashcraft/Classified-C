
#ifndef THREAD_H
#define THREAD_H

#include "LinkedList.h"

extern Class ThreadClass;

typedef struct _Thread {
	struct _Object base;
	Object target;
	cstring selector;
	LinkedList userData;
	pthread_t thread;
	Stack autoReleasePools;
} *Thread;

void ThreadInit();
Thread current_thread();

#endif