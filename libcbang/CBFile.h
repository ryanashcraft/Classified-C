
#ifndef CB_FILE_H
#define CB_FILE_H

typedef struct _CBFile {
	class type;
	string filename;
	FILE *file;
	struct _CBObject parent;
} *CBFile;

class cbfile_init();

#endif
