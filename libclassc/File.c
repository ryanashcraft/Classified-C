
#include "Classified-C.h"

#define TYPE File
#define SUPER ObjectClass

proto(newWithFilename)
proto(newWithFile)
proto(initWithFilename)
proto(initWithFile)
proto(dealloc)
proto(file)

defclass
	registerStatic("newWithFilename", newWithFilename);
	registerStatic("newWithFile", newWithFile);
	
	register("initWithFilename", initWithFilename);
	register("initWithFile", initWithFilename);
	register("dealloc", dealloc);
	register("file", file);
end

defcon(newWithFilename)
	initWithFilename(self, args);

	return self;
end

defcon(newWithFile)
	initWithFile(self, args);

	return self;
end

def(initWithFilename)
	self->filename = mstring(NEXT_ARG(cstring));
	self->file = fopen(self->filename, "r");

	return self;
end

def(initWithFile)
	self->filename = NULL;
	self->file = NEXT_ARG(FILE *);

	return self;
end

def(dealloc)
	fclose(self->file);
	if (self->filename) {
		free(self->filename);
	}

	return msg_cast(ObjectClass, self, "dealloc");
end

def(file)
	return self->file;
end
