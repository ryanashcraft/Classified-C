
#ifndef CB_FILE_H
#define CB_FILE_H

extern Class FileClass;

typedef struct _CBFile {
	Class class;
	list *methods;
	string filename;
	FILE *file;
	struct _CBObject parent;
} *File;

void file_class_init();

#endif
