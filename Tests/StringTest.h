
#ifndef STRING_TEST_CASE_H
#define STRING_TEST_CASE_H

extern Class StringTestClass;

typedef struct _StringTest {
	struct _Test base;
} *StringTest;

void string_test_class_init();

#endif
