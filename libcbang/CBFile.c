
#include "CBang.h"
#include "CBFile.h"

Class FileClass = NULL;

static void *initWithFilename(void *v, va_list *args);
static void *super(void *v);

static void *release(void *v, va_list *args);

void file_class_init() {
	method m;

	FileClass = message(ClassClass, "init", "FileClass", ObjectClass, &super);

	m = mmethod(mstring("initWithFilename"), &initWithFilename);
	push_back(FileClass->methods, m);
	m = mmethod(mstring("release"), &release);
	push_back(FileClass->methods, m);
}

void *initWithFilename(void *v, va_list *args) {
	File f;
	method m;

	f = calloc(1, sizeof(struct _CBFile));
	assert(f);

	f->class = FileClass;
	f->filename = mstring(va_arg(*args, string));
	f->file = fopen(f->filename, "r");

	f->methods = create_list();
	m = mmethod(mstring("release"), &release);
	push_back(f->methods, m);

	message(ObjectClass, "initWithPointer", &(f->parent));

	return f;
}

void *super(void *v) {
	File f = (File)v;
	return &(f->parent);
}

void *release(void *v, va_list *args) {
	File f = (File)v;
	fclose(f->file);
	free(f->filename);
	return f;
}
