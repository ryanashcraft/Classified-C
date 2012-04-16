
#ifndef CB_SCANNER_H
#define CB_SCANNER_H

extern Class ScannerClass;

typedef struct _CBScanner {
	Class class;
	list *methods;
	Object parent;
	File file;
} *Scanner;

void scanner_class_init();

#endif
