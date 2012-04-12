
#ifndef CB_SCANNER_H
#define CB_SCANNER_H

typedef struct _CBScanner {
	class type;
	CBFile file;
	struct _CBObject parent;
} *CBScanner;

class cbscanner_init();

#endif
