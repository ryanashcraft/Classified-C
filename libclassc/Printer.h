
#ifndef LOG_H
#define LOG_H

extern Class PrinterClass;

typedef struct _Printer {
	struct _Object base;
	File output;
} *Printer;

void printer_class_init();

#endif
