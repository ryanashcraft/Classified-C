
#include "CBang.h"
#include "CBString.h"
#include "CBInteger.h"

static class this = NULL;

static void *constructor(void *v, void **p, va_list *args);
static void destructor(void *v);
static void *super(void *);

static void *concatenate(void *v, va_list *args);
static void *length(void *v, va_list *args);
static void *print(void *v, va_list *args);

class cbstring_init() {
	method m;

	if (this) {
		return this;
	}

	this = mclass(mstring("CBString"), NULL, &constructor, &destructor, &super);

	m = mmethod(mstring("concatenate"), &concatenate);
	push_back(this->methods, m);
	m = mmethod(mstring("length"), &length);
	push_back(this->methods, m);
	m = mmethod(mstring("print"), &print);
	push_back(this->methods, m);

	return this;
}

void *constructor(void *v, void **p, va_list *args) {
	CBString s;
	if (!v) {
		s = malloc(sizeof(struct _CBString));
		assert(s);
	} else {
		s = (CBString)v;
	}
	
	s->type = this;
	s->value = mstring(va_arg(*args, string));

	*p = &s->parent;

	return s;
}

void destructor(void *v) {
	CBString s = (CBString)v;
	free(s->value);
}

void *super(void *v) {
	CBString s = (CBString)v;
	return &s->parent;
}

void *concatenate(void *v, va_list *args) {
	CBString s = (CBString)v;

	string part_one = s->value;
	string part_two = mstring(va_arg(*args, string));
	int part_one_length = strlen(part_one);
	int part_two_length = strlen(part_two);

	part_one = realloc(part_one, part_one_length + part_two_length + 1);
	assert(part_one);
 	
	strncat(part_one, part_two, part_two_length);

	s->value = part_one;

	return NULL;
}

void *length(void *v, va_list *args) {
	CBString s = (CBString)v;
	CBInteger length = construct("CBInteger", strlen(s->value));
	return length;
}

void *print(void *v, va_list *args) {
	CBString s = (CBString)v;
	printf("%s", s->value);
	return NULL;
}