
#ifndef BOOLEAN_H
#define BOOLEAN_H

extern Class BooleanClass;

typedef struct _Boolean {
	struct _Integer base;	
} *Boolean;

void boolean_class_init();

#endif
