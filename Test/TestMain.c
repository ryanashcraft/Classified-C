
#include "../libclassc/classified-c.h"
#include "Test.h"
#include "StringTest.h"

int main(int argc, char **argv) {
	cc_init();
	test_class_init();
	string_test_class_init();
	
	Test stringTest = msg(StringTestClass, "new");
	msg(stringTest, "run");
	msg(stringTest, "release");
}