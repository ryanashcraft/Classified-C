
#ifndef CB_SCANNER_H
#define CB_SCANNER_H

extern Class ScannerClass;

typedef struct _CBScanner {
	OBJECT_BASE
	
	File file;
} *Scanner;

void scanner_class_init();

#endif
