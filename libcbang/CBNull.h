
#ifndef CB_NULL_H
#define CB_NULL_H

extern Class NullClass;

typedef struct _CBNull {
	Class class;
	list *methods;
	struct _CBObject parent;
} *Null;

void null_class_init();

#endif
