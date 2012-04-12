
#include "CBang.h"
#include "CBFile.h"

static class this = NULL;

static void *constructor(void *v, void **p, va_list *args);
static void destructor(void *v);
static void *super(void *v);

class cbfile_init() {
	if (this) {
		return this;
	}

	this = mclass(mstring("CBFile"), NULL, &constructor, &destructor, &super);

	return this;
}

void *constructor(void *v, void **p, va_list *args) {
	CBFile f;
	if (!v) {
		f = calloc(1, sizeof(struct _CBFile));
		assert(f);
	} else {
		f = (CBFile)v;
	}

	f->type = this;
	f->filename = mstring(va_arg(*args, string));
	f->file = fopen(f->filename, "r");

	*p = &f->parent;

	return f;
}

void destructor(void *v) {
	CBFile f = (CBFile)v;
	fclose(f->file);
	free(f->filename);
}

void *super(void *v) {
	CBFile f = (CBFile)v;
	return &f->parent;
}