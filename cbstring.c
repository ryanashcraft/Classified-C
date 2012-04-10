
#include "cbang.h"
#include "cbstring.h"

static class *this = NULL;

static var constructor();
static var concatenate();

string cbstring_to_string(var v) {
	return ((struct _cbstring_data *)v->data)->value;
}

class *cbstring_init() {
	method *method;

	if (this) {
		return this;
	}

	this = mclass(mstring("CBString"), &constructor);

	method = mmethod(mstring("concatenate"), &concatenate);
	push_back(this->methods, method);

	return this;
}

var constructor(va_list args) {
	var the_var = mvar(this);

	the_var->data = malloc(sizeof(struct _cbstring_data));
	((struct _cbstring_data *)the_var->data)->value = va_arg(args, string);

	return the_var;
}

var concatenate(var v, va_list args) {
	string part_one = ((struct _cbstring_data *)v->data)->value;
	string part_two = va_arg(args, string);
	int part_one_length = strlen(part_one);
	int part_two_length = strlen(part_two);

	realloc(part_one, sizeof(char) * (part_one_length + part_two_length + 1));

	memcpy(&part_one[part_one_length - 1], part_two, sizeof(char) * (part_two_length + 1));

	free(part_two);

	return NULL;
}