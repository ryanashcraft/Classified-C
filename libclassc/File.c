
#include "Classified-C.h"

#define CLASS File
#define SUPER Object

proto(newWithFilename);
proto(newWithFile);
proto(initWithFilename);
proto(initWithFile);
proto(dealloc);
proto(file);

defclass {
	constructor(newWithFilename);
	constructor(newWithFile);
	
	instance(initWithFilename);
	instance(initWithFilename);
	instance(dealloc);
	instance(file);
} end

defcon(newWithFilename) {
	initWithFilename(self, args);

	return self;
} end

defcon(newWithFile) {
	initWithFile(self, args);

	return self;
} end

def(initWithFilename) {
	self->filename = mstring(nextArg(cstring));
	self->file = fopen(self->filename, "r");

	return self;
} end

def(initWithFile) {
	self->filename = NULL;
	self->file = nextArg(FILE *);

	return self;
} end

def(dealloc) {
	fclose(self->file);
	if (self->filename) {
		free(self->filename);
	}

	return msgSuper("dealloc");
} end

def(file) {
	return self->file;
} end
