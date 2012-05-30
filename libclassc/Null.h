
#ifndef NULL_H
#define NULL_H

extern Class NullClass;

typedef struct _Null {
	struct _Object base;
} *Null;

void null_class_init();

#endif
