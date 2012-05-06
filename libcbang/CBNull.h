
#ifndef CB_NULL_H
#define CB_NULL_H

extern Class NullClass;

typedef struct _CBNull {
	struct _CBObject base;
} *Null;

void null_class_init();

#endif
