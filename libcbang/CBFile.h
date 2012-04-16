
#ifndef CB_FILE_H
#define CB_FILE_H

extern Class FileClass;

typedef struct _CBFile {
	OBJECT_BASE
	
	string filename;
	FILE *file;
} *File;

void file_class_init();

#endif
