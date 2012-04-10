
#include "cbang.h"
#include "cbstring.h"

static class *this = NULL;

static var constructor();

string cbstring_to_string(var v) {
	return ((struct _cbstring_data *)v->data)->value;
}

class *cbstring_init() {
	if (this) {
		return this;
	}

	this = mclass(mstring("CBString"), &constructor);

	return this;
}

var constructor(va_list args) {
	var the_var = mvar(this);

	the_var->data = malloc(sizeof(struct _cbstring_data));
	((struct _cbstring_data *)the_var->data)->value = va_arg(args, string);

	return the_var;
}