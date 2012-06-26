
#define CLASS Printer
#define SUPER Object

#include "Classified-C.h"

proto(newWithFile);
proto(initWithFile);
proto(dealloc);
proto(print);
proto(println);
proto(flush);
proto(printEach);
proto(disable);

defclass
	constructor(newWithFile);
	
	instance(initWithFile);
	instance(dealloc);
	instance(print);
	instance(println);
	instance(flush);
	instance(printEach);
	instance(disable);
end

defcon(newWithFile)
	initWithFile(self, args);

	return self;
end

def(initWithFile)
	self->output = nextArg(File);

	return self;
end

def(dealloc)
	msg(self->output, "release");

	return msgSuper("dealloc");
end

def(print)
	if (self->disabled) {
		return self;
	}

	cstring format = nextArg(cstring);
	String toPrint = msg(StringClass, "newWithFormatCStringAndArgList", format, args);
	fprintf(self->output->file, "%s", toPrint->value);
	msg(toPrint, "release");

	return self;
end

def(println)
	if (self->disabled) {
		return self;
	}

	String toPrint = msg(StringClass, "newWithFormatCStringAndArgList", nextArg(cstring), args);
	fprintf(self->output->file, "%s\n", toPrint->value);
	msg(toPrint, "release");

	return self;
end

def(flush)
	if (self->disabled) {
		return self;
	}

	fflush(self->output->file);

	return self;
end

def(printEach)
	if (self->disabled) {
		return self;
	}

	cstring separator = nextArg(cstring);
	Array elements = nextArg(Array);

	Object element = NULL;
	Iterator iterator = msg(IteratorClass, "newWithArray", elements);
	while ( (element = msg(iterator, "next")) ) {
		String toPrint = msg(StringClass, "newWithFormatCString", "%@%s", element, separator);
		fprintf(self->output->file, "%s", toPrint->value);
		msg(toPrint, "release");
	}
	msg(iterator, "release");

	return self;
end

def(disable)
	self->disabled = YES;

	return self;
end
