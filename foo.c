
#include "cbang.h"
#include "cbstring.h"

int main(int argc, char **argv) {
	cbang_init();

	var s = cbang_constructor("CBString", mstring("foo "));
	
	cbang_message_send(s, "concatenate", mstring(" fighter"));

	printf("%s", cbstring_to_string(s));

	printf("\n");
}
