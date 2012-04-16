
#include "CBang.h"
#include "CBFile.h"

Class FileClass = NULL;

static void *initWithFilename(void *v, va_list *args);

static void *release(void *v, va_list *args);

void file_class_init() {
	method m;

	FileClass = message(ClassClass, "init", "FileClass", ObjectClass);

	m = mmethod("initWithFilename", &initWithFilename);
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
	m = mmethod("release", &release);
	push_back(f->methods, m);

	f->parent = message(ObjectClass, "init");

	return f;
}

void *release(void *v, va_list *args) {
	File f = (File)v;
	fclose(f->file);
	free(f->filename);
	message(f->parent, "release");
	free_list(f->methods, free);
	free(f);
	return f;
}
