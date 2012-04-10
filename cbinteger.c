
#include "CBang.h"
#include "CBInteger.h"

static class this = NULL;

static var constructor();

int cbinteger_to_int(var v) {
	return ((struct _cbinteger_data *)v->data)->value;
}

class cbinteger_init() {
	if (this) {
		return this;
	}

	this = mclass(mstring("CBInteger"), NULL, &constructor);

	return this;
}

var constructor(va_list args) {
	var v = mvar(this);

	v->data = malloc(sizeof(struct _cbinteger_data));
	((struct _cbinteger_data *)v->data)->value = va_arg(args, int);

	return v;
}