
#include "Classified-C.h"

IMPLEMENTATION(FileClass);

PROTOTYPE(newWithFilename);
PROTOTYPE(newWithFile);
PROTOTYPE(initWithFilename);
PROTOTYPE(initWithFile);
PROTOTYPE(dealloc);
PROTOTYPE(file);

void file_class_init() {
	FileClass = msg(ClassClass, "new", "File", ObjectClass);

	REGISTER_CLASS_METHOD(FileClass, "newWithFilename", newWithFilename);
	REGISTER_CLASS_METHOD(FileClass, "newWithFile", newWithFile);
	
	REGISTER_METHOD(FileClass, "initWithFilename", initWithFilename);
	REGISTER_METHOD(FileClass, "initWithFile", initWithFilename);
	REGISTER_METHOD(FileClass, "dealloc", dealloc);
	REGISTER_METHOD(FileClass, "file", file);
}

DEFINE(newWithFilename) {
	NEW(FileClass, struct _File);

	initWithFilename(self, args);

	return self;
}

DEFINE(newWithFile) {
	NEW(FileClass, struct _File);

	initWithFile(self, args);

	return self;
}

DEFINE(initWithFilename) {
	CONTEXT(File);

	self->filename = mstring(NEXT_ARG(cstring));
	self->file = fopen(self->filename, "r");

	return self;
}

DEFINE(initWithFile) {
	CONTEXT(File);
	
	self->filename = NULL;
	self->file = NEXT_ARG(FILE *);

	return self;
}

DEFINE(dealloc) {
	CONTEXT(File);

	fclose(self->file);
	if (self->filename) {
		free(self->filename);
	}

	return msg_cast(ObjectClass, self, "dealloc");
}

DEFINE(file) {
	CONTEXT(File);

	return self->file;
}
