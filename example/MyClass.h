
#ifndef MY_STRING_H
#define MY_STRING_H

extern Class FooClass;

typedef struct _MyClass {
	Class class;
	list *methods;
	string name;
	int value;
	struct _CBString parent;
} *Foo;

void foo_class_init();

#endif
