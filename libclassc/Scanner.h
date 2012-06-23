
#ifndef SCANNER_H
#define SCANNER_H

extern Class ScannerClass;

typedef struct _Scanner {
	struct _Object base;
	File file;
} *Scanner;

void ScannerInit();

#endif
