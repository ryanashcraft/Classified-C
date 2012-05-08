
#ifndef CB_FILE_H
#define CB_FILE_H

extern Class FileClass;

typedef struct _CBFile {
	struct _CBObject base;
	string filename;
	FILE *file;
} *File;

void file_class_init();

#endif
