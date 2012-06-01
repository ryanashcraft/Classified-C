
#ifndef TEST_CASE_H
#define TEST_CASE_H

typedef int (*test_case_func) (void);

extern Class TestCaseClass;

typedef struct _TestCase {
	struct _Object base;
	test_case_func function;
} *TestCase;

void test_case_class_init();

#endif
