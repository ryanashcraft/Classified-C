
#include "Classified-C.h"

Class PrinterClass = NULL;

static void *newWithFile(void *v, va_list *args);

static void *initWithFile(void *v, va_list *args);
static void *dealloc(void *v, va_list *args);
static void *print(void *v, va_list *args);
static void *println(void *v, va_list *args);
static void *flush(void *v, va_list *args);
static void *printEach(void *v, va_list *args);

void printer_class_init() {
	PrinterClass = msg(ClassClass, "new", "Printer", ObjectClass);

	push_back(PrinterClass->static_methods, mmethod("newWithFile", &newWithFile));
	
	push_back(PrinterClass->instance_methods, mmethod("initWithFile", &initWithFile));
	push_back(PrinterClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(PrinterClass->instance_methods, mmethod("print", &print));
	push_back(PrinterClass->instance_methods, mmethod("println", &println));
	push_back(PrinterClass->instance_methods, mmethod("flush", &flush));
	push_back(PrinterClass->instance_methods, mmethod("printEach", &printEach));
}

void *newWithFile(void *v, va_list *args) {
	Printer o = cc_alloc(sizeof(struct _Printer));
	initWithFile(o, args);
	((Object)o)->root = PrinterClass;
	return o;
}

void *initWithFile(void *v, va_list *args) {
	Printer o = (Printer)v;
	msg_cast(ObjectClass, o, "init");
	o->output = va_arg(*args, File);
	return o;
}

void *dealloc(void *v, va_list *args) {
	Printer o = (Printer)v;
	msg(o->output, "release");
	return msg_cast(ObjectClass, o, "dealloc");
}

void *print(void *v, va_list *args) {
	Printer o = (Printer)v;
	cstring format = va_arg(*args, cstring);
	String toPrint = msg(StringClass, "newWithFormatCStringAndArgList", format, args);
	fprintf(o->output->file, "%s", toPrint->value);
	msg(toPrint, "release");
	return NULL;
}

void *println(void *v, va_list *args) {
	Printer o = (Printer)v;
	String toPrint = msg(StringClass, "newWithFormatCStringAndArgList", va_arg(*args, cstring), args);
	fprintf(o->output->file, "%s\n", toPrint->value);
	msg(toPrint, "release");
	return NULL;
}

void *flush(void *v, va_list *args) {
	Printer o = (Printer)v;
	fflush(o->output->file);
	return o;
}

void *printEach(void *v, va_list *args) {
	Printer o = (Printer)v;

	cstring separator = va_arg(*args, cstring);
	Array elements = va_arg(*args, Array);

	Object element = NULL;
	Iterator iterator = msg(IteratorClass, "newWithArray", elements);
	while ( (element = msg(iterator, "next")) ) {
		String description = msg(element, "description");
		String toPrint = msg(StringClass, "newWithFormatCString", "%@%s", description, separator);
		fprintf(o->output->file, "%s", toPrint->value);
		msg(description, "release");
		msg(toPrint, "release");
	}
	msg(iterator, "release");

	return o;
}
