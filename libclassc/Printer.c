
#include "Classified-C.h"

IMPLEMENTATION(PrinterClass);

PROTOTYPE(newWithFile);
PROTOTYPE(initWithFile);
PROTOTYPE(dealloc);
PROTOTYPE(print);
PROTOTYPE(println);
PROTOTYPE(flush);
PROTOTYPE(printEach);

void printer_class_init() {
	PrinterClass = msg(ClassClass, "new", "Printer", ObjectClass);

	REGISTER_CLASS_METHOD(PrinterClass, "newWithFile", newWithFile);
	
	REGISTER_METHOD(PrinterClass, "initWithFile", initWithFile);
	REGISTER_METHOD(PrinterClass, "dealloc", dealloc);
	REGISTER_METHOD(PrinterClass, "print", print);
	REGISTER_METHOD(PrinterClass, "println", println);
	REGISTER_METHOD(PrinterClass, "flush", flush);
	REGISTER_METHOD(PrinterClass, "printEach", printEach);
}

DEFINE(newWithFile) {
	NEW(PrinterClass, struct _Printer);

	initWithFile(self, args);

	return self;
}

DEFINE(initWithFile) {
	CONTEXT(Printer);

	self->output = NEXT_ARG(File);

	return self;
}

DEFINE(dealloc) {
	CONTEXT(Printer);

	msg(self->output, "release");

	return msg_cast(ObjectClass, self, "dealloc");
}

DEFINE(print) {
	CONTEXT(Printer);

	cstring format = NEXT_ARG(cstring);
	String toPrint = msg(StringClass, "newWithFormatCStringAndArgList", format, args);
	fprintf(self->output->file, "%s", toPrint->value);
	msg(toPrint, "release");

	return self;
}

DEFINE(println) {
	CONTEXT(Printer);

	String toPrint = msg(StringClass, "newWithFormatCStringAndArgList", NEXT_ARG(cstring), args);
	fprintf(self->output->file, "%s\n", toPrint->value);
	msg(toPrint, "release");

	return self;
}

DEFINE(flush) {
	CONTEXT(Printer);

	fflush(self->output->file);

	return self;
}

DEFINE(printEach) {
	CONTEXT(Printer);

	cstring separator = NEXT_ARG(cstring);
	Array elements = NEXT_ARG(Array);

	Object element = NULL;
	Iterator iterator = msg(IteratorClass, "newWithArray", elements);
	while ( (element = msg(iterator, "next")) ) {
		String toPrint = msg(StringClass, "newWithFormatCString", "%@%s", element, separator);
		fprintf(self->output->file, "%s", toPrint->value);
		msg(toPrint, "release");
	}
	msg(iterator, "release");

	return self;
}
