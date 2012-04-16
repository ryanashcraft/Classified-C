
#ifndef CB_NULL_H
#define CB_NULL_H

extern Class NullClass;

typedef struct _CBNull {
	OBJECT_BASE
} *Null;

void null_class_init();

#endif
