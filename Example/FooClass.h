
#ifndef MY_STRING_H
#define MY_STRING_H

extern Class FooClass;

typedef struct _Foo {
	struct _CBString base;
	int value;
} *Foo;

void foo_class_init();

#endif
