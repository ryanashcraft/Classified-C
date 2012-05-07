
#include "CBang.h"

Class PrinterClass = NULL;

static void *new(void *v, va_list *args);

static void *init(void *v, va_list *args);
static void *dealloc(void *v, va_list *args);
static void *print(void *v, va_list *args);
static void *println(void *v, va_list *args);

void printer_class_init() {
	PrinterClass = msg_class(ClassClass, "new", "Printer", ObjectClass);

	push_back(PrinterClass->static_methods, mmethod("new", &new));
	
	push_back(PrinterClass->instance_methods, mmethod("init", &init));
	push_back(PrinterClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(PrinterClass->instance_methods, mmethod("print", &print));
	push_back(PrinterClass->instance_methods, mmethod("println", &println));
}

void *new(void *v, va_list *args) {
	Printer o = cballoc(sizeof(struct _CBPrinter));
	init(o, args);
	((Object)o)->root = PrinterClass;
	return o;
}

void *init(void *v, va_list *args) {
	Printer o = (Printer)v;
	msg_cast(ObjectClass, o, "init");
	return o;
}

void *dealloc(void *v, va_list *args) {
	Printer o = (Printer)v;
	return msg_cast(ObjectClass, o, "dealloc");
}

void *print(void *v, va_list *args) {
	// Printer o = (Printer)void;
	String toPrint = msg_class(StringClass, "newWithFormat", va_arg(*args, string), args);
	fprintf(stdout, "%s", toPrint->value);
	msg(toPrint, "release");
	return NULL;
}

void *println(void *v, va_list *args) {
	String toPrint = msg_class(StringClass, "newWithFormat", va_arg(*args, string), args);
	fprintf(stdout, "%s\n", toPrint->value);
	msg(toPrint, "release");

	return NULL;
}
