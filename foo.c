
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cbang.h"

int main(int argc, char **argv) {
	var temp;
	cbang_init();

	var a_null = cbang_constructor("CBNull");
	temp = cbang_message_send(a_null, "describe");

	printf("\n");
}
