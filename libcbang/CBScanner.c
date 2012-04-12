
#include "CBang.h"
#include "CBScanner.h"

#define TOKEN_BUFFER_SIZE 256

static class this = NULL;

static void *constructor(void *v, void **p, va_list *args);
static void destructor(void *v);
static void *super(void *v);

static void *next(void *v, va_list *args);
static void *has_next(void *v, va_list *args);

class cbscanner_init() {
	method m;

	if (this) {
		return this;
	}

	this = mclass(mstring("CBScanner"), NULL, &constructor, &destructor, &super);

	m = mmethod(mstring("next"), &next);
	push_back(this->methods, m);
	m = mmethod(mstring("has_next"), &has_next);
	push_back(this->methods, m);

	return this;
}

void *constructor(void *v, void **p, va_list *args) {
	CBScanner s;
	if (!v) {
		s = calloc(1, sizeof(struct _CBScanner));
		assert(s);
	} else {
		s = (CBScanner)v;
	}

	s->type = this;
	s->file = va_arg(*args, CBFile);

	*p = &s->parent;

	return s;
}

void destructor(void *v) {
}

void *super(void *v) {
	CBScanner s = (CBScanner)v;
	return &s->parent;
}

void *next(void *v, va_list *args) {
	CBScanner s = (CBScanner)v;
	FILE *f = s->file->file;

	string buffer = calloc(1, TOKEN_BUFFER_SIZE);
	assert(buffer);
	char c;
	int i;

	i = 0;
	getcloop:
    do {
		c = fgetc(f);

		if (c == EOF || c < 33) {
			if (i == 0) {
				goto getcloop;
			}

			break;
		}
		
		buffer[i] = c;
	} while (++i);

	CBString token = construct("CBString", buffer);

	free(buffer);

	return token;
}

void *has_next(void *v, va_list *args) {
	CBScanner s = (CBScanner)v;
	FILE *f = s->file->file;
	int has_next = 1;
	char c = 0;

	c = fgetc(f);
	if (c == EOF) {
		has_next = 0;
	}
	ungetc(c, f);

	CBInteger retval = construct("CBInteger", has_next);

	return retval;
}