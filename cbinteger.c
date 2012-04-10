
#include "cbang.h"
#include "cbinteger.h"

static class this = NULL;

static var constructor();

int cbinteger_to_int(var v) {
	return ((struct _cbinteger_data *)v->data)->value;
}

class cbinteger_init() {
	if (this) {
		return this;
	}

	this = mclass(mstring("CBInteger"), &constructor);

	return this;
}

var constructor(va_list args) {
	var the_var = mvar(this);

	the_var->data = malloc(sizeof(struct _cbinteger_data));
	((struct _cbinteger_data *)the_var->data)->value = va_arg(args, int);

	return the_var;
}