
#include "CBang.h"

Class FileClass = NULL;

static void *newWithFilename(void *v, va_list *args);
static void *newWithFile(void *v, va_list *args);

static void *initWithFilename(void *v, va_list *args);
static void *initWithFile(void *v, va_list *args);
static void *dealloc(void *v, va_list *args);
static void *file(void *v, va_list *args);

void file_class_init() {
	FileClass = msg(ClassClass, "new", "File", ObjectClass);

	push_back(FileClass->static_methods, mmethod("newWithFilename", &newWithFilename));
	push_back(FileClass->static_methods, mmethod("newWithFile", &newWithFile));
	
	push_back(FileClass->instance_methods, mmethod("initWithFilename", &initWithFilename));
	push_back(FileClass->instance_methods, mmethod("initWithFile", &initWithFilename));
	push_back(FileClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(FileClass->instance_methods, mmethod("file", &file));
}

void *newWithFilename(void *v, va_list *args) {
	String o = cballoc(sizeof(struct _CBFile));
	initWithFilename(o, args);
	((Object)o)->root = FileClass;
	return o;
}

void *newWithFile(void *v, va_list *args) {
	String o = cballoc(sizeof(struct _CBFile));
	initWithFile(o, args);
	((Object)o)->root = FileClass;
	return o;
}

void *initWithFilename(void *v, va_list *args) {
	File o = (File)v;
	msg_cast(ObjectClass, o, "init");
	o->filename = mstring(va_arg(*args, cstring));
	o->file = fopen(o->filename, "r");
	return o;
}

void *initWithFile(void *v, va_list *args) {
	File o = (File)v;
	msg_cast(ObjectClass, o, "init");
	o->filename = NULL;
	o->file = va_arg(*args, FILE *);
	return o;
}

void *dealloc(void *v, va_list *args) {
	File o = (File)v;
	fclose(o->file);
	if (o->filename) {
		free(o->filename);
	}
	return msg_cast(ObjectClass, o, "dealloc");
}

static void *file(void *v, va_list *args) {
	File o = (File)v;
	return o->file;
}
