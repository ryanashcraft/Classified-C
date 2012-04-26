
#include "CBang.h"
#include "CBFile.h"

Class FileClass = NULL;

typedef struct _CBFile {
	OBJECT_BASE
	
	string filename;
	FILE *file;
} *File;

static void *initWithFilename(void *v, va_list *args);

static void *dealloc(void *v, va_list *args);
static void *file(void *v, va_list *args);

void file_class_init() {
	FileClass = msg(ClassClass, "init", "File", ObjectClass);

	push_back(FileClass->methods, mmethod("initWithFilename", &initWithFilename));
	
	push_back(FileClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(FileClass->instance_methods, mmethod("file", &file));
}

void *initWithFilename(void *v, va_list *args) {
	File o;

	o = calloc(1, sizeof(struct _CBFile));
	assert(o);

	Object root = va_arg(*args, Object);
	if (!root) {
		root = (Object)o;
	}

	o->class = FileClass;
	o->methods = FileClass->instance_methods;
	o->parent = msg(ObjectClass, "init", o);
	o->root = root;

	o->filename = mstring(va_arg(*args, string));
	o->file = fopen(o->filename, "r");

	return o;
}

void *dealloc(void *v, va_list *args) {
	File o = (File)v;
	msg(o->parent, "dealloc");
	fclose(o->file);
	free(o->filename);
	free(o);
	return NULL;
}

static void *file(void *v, va_list *args) {
	File o = (File)v;
	return o->file;
}
