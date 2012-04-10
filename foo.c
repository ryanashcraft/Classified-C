
#include "cbang.h"
#include "cbstring.h"
#include "cbinteger.h"

int main(int argc, char **argv) {
	cbang_init();

	var s = construct("CBString", mstring("foo"));
	message(s, "concatenate", mstring(" fighter"));
	printf("%s\n", cbstring_to_string(s));

	var i = message(s, "length");
	printf("%d\n", cbinteger_to_int(i));
	release(i);
	release(s);

	printf("\n");
}
