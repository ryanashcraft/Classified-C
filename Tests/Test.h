
#ifndef TEST_H
#define TEST_H

extern Class TestClass;

typedef enum {
	TestCaseResultSuccess,
	TestCaseResultFailure
} TestCaseResult;

typedef struct _Test {
	struct _Object base;
	LinkedList testCases;
} *Test;

void TestInit();

#endif
