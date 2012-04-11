
#ifndef MY_STRING_H
#define MY_STRING_H

typedef struct _MyClass {
	struct _CBString parent;
	int value;
} *MyClass;

class myclass_init();

#endif