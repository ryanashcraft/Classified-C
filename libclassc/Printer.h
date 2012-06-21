
#ifndef LOG_H
#define LOG_H

extern Class PrinterClass;

typedef struct _Printer {
	struct _Object base;
	File output;
	boolean disabled;
} *Printer;

void printer_class_init();

#endif
