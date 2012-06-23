
#ifndef Foo_H
#define Foo_H

extern Class FooClass;

typedef struct _Foo {
	struct _String base;
	int value;
} *Foo;

void FooInit();

#endif
