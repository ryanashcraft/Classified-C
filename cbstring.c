
#include "CBang.h"
#include "CBString.h"

static class this = NULL;

static void *constructor(va_list args);
static void destructor(void *v);
static void *concatenate(void *v, va_list args);
static void *length(void *v, va_list args);
static void *print(void *v, va_list args);

string cbstring_to_string(CBString v) {
	if (!v) {
		return NULL;
	}

	return v->value;
}

class cbstring_init() {
	method m;

	if (this) {
		return this;
	}

	this = mclass(mstring("CBString"), NULL, &constructor, &destructor);

	m = mmethod(mstring("concatenate"), &concatenate);
	push_back(this->methods, m);
	m = mmethod(mstring("length"), &length);
	push_back(this->methods, m);
	m = mmethod(mstring("print"), &print);
	push_back(this->methods, m);

	return this;
}

void *constructor(va_list args) {
	CBString v = malloc(sizeof(struct _CBString));
	assert(v);
	v->meta.type = this;
	v->meta.parent = NULL;

	v->value = va_arg(args, string);

	return v;
}

void destructor(void *v) {
	CBString s = (CBString)s;
	free(s->value);
}

void *concatenate(void *v, va_list args) {
	CBString s = (CBString)v;

	string part_one = s->value;
	string part_two = va_arg(args, string);
	int part_one_length = strlen(part_one);
	int part_two_length = strlen(part_two);

	realloc(part_one, sizeof(char) * (part_one_length + part_two_length + 1));

	memcpy(&part_one[part_one_length], part_two, sizeof(char) * (part_two_length + 1));

	free(part_two);

	return NULL;
}

void *length(void *v, va_list args) {
	CBString s = (CBString)v;
	var length = construct("CBInteger", strlen(cbstring_to_string(s)));
	return length;
}

void *print(void *v, va_list args) {
	CBString s = (CBString)s;
	printf("%s", cbstring_to_string(s));
	return NULL;
}