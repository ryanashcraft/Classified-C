
#include "../libclassc/classified-c.h"
#include "Test.h"
#include "StringTest.h"

int main(int argc, char **argv) {
	cc_init();
	TestInit();
	StringTestInit();
	
	int i = 100;
	msg(systemOut, "disable");
	while (--i > 0) {
		Test stringTest = msg(StringTestClass, "new");
		msg(stringTest, "run");
		msg(stringTest, "release");
	}
}
