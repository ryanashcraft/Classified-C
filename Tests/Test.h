
#ifndef TEST_H
#define TEST_H

extern Class TestClass;

typedef struct _Test {
	struct _Object base;
	LinkedList testCases;
} *Test;

void test_class_init();

#endif
