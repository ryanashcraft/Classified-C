
#ifndef MY_STRING_H
#define MY_STRING_H

extern Class FooClass;

typedef struct _Foo {
	OBJECT_BASE

	int value;
} *Foo;

void foo_class_init();

#endif
