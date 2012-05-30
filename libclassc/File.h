
#ifndef FILE_H
#define FILE_H

extern Class FileClass;

typedef struct _File {
	struct _Object base;
	cstring filename;
	FILE *file;
} *File;

void file_class_init();

#endif
