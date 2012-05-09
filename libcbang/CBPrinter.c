
#include "CBang.h"

Class PrinterClass = NULL;

static void *newWithFile(void *v, va_list *args);

static void *initWithFile(void *v, va_list *args);
static void *dealloc(void *v, va_list *args);
static void *print(void *v, va_list *args);
static void *println(void *v, va_list *args);
static void *flush(void *v, va_list *args);

void printer_class_init() {
	PrinterClass = msg(ClassClass, "new", "Printer", ObjectClass);

	push_back(PrinterClass->static_methods, mmethod("newWithFile", &newWithFile));
	
	push_back(PrinterClass->instance_methods, mmethod("initWithFile", &initWithFile));
	push_back(PrinterClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(PrinterClass->instance_methods, mmethod("print", &print));
	push_back(PrinterClass->instance_methods, mmethod("println", &println));
	push_back(PrinterClass->instance_methods, mmethod("flush", &flush));
}

void *newWithFile(void *v, va_list *args) {
	Printer o = cballoc(sizeof(struct _CBPrinter));
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
	string format = va_arg(*args, string);
	String toPrint = msg(StringClass, "newWithFormatAndArgList", format, args);
	fprintf(o->output->file, "%s", toPrint->value);
	msg(toPrint, "release");
	return NULL;
}

void *println(void *v, va_list *args) {
	Printer o = (Printer)v;
	String toPrint = msg(StringClass, "newWithFormatAndArgList", va_arg(*args, string), args);
	fprintf(o->output->file, "%s\n", toPrint->value);
	msg(toPrint, "release");
	return NULL;
}

void *flush(void *v, va_list *args) {
	Printer o = (Printer)v;
	fflush(o->output->file);
	return o;
}
