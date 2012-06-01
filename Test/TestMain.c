
#include "../libclassc/classified-c.h"
#include "Test.h"

int main(int argc, char **argv) {
	cc_init();
	test_class_init();
	
	Test testCase = msg(TestClass, "new");

	msg(SystemOut, "println", "%@", testCase);
}