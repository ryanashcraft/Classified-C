
#ifndef CB_LOG_H
#define CB_LOG_H

extern Class PrinterClass;

typedef struct _CBPrinter {
	struct _CBObject base;
} *Printer;

void printer_class_init();

#endif
