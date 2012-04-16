
#include "CBang.h"
#include "CBFile.h"

Class FileClass = NULL;

static void *initWithFilename(void *v, va_list *args);

static void *release(void *v, va_list *args);

void file_class_init() {
	method m;

	FileClass = message(ClassClass, "init", "File", ObjectClass);

	m = mmethod("initWithFilename", &initWithFilename);
	push_back(FileClass->methods, m);

	m = mmethod("release", &release);
	push_back(FileClass->instance_methods, m);
}

void *initWithFilename(void *v, va_list *args) {
	File o;

	o = calloc(1, sizeof(struct _CBFile));
	assert(o);

	o->class = FileClass;
	o->methods = FileClass->instance_methods;
	o->parent = message(ObjectClass, "init");

	o->filename = mstring(va_arg(*args, string));
	o->file = fopen(o->filename, "r");

	return o;
}

void *release(void *v, va_list *args) {
	File o = (File)v;
	fclose(o->file);
	free(o->filename);
	message(o->parent, "release");
	free(o);
	return o;
}
