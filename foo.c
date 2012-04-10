
#include "cbang.h"
#include "cbstring.h"
#include "cbinteger.h"

int main(int argc, char **argv) {
	cbang_init();

	var s = cbang_constructor("CBString", mstring("foo"));
	cbang_message_send(s, "concatenate", mstring(" fighter"));
	printf("%s\n", cbstring_to_string(s));

	var i = cbang_message_send(s, "length");
	printf("%d\n", cbinteger_to_int(i));
	cbang_release(i);
	cbang_release(s);

	printf("\n");
}
