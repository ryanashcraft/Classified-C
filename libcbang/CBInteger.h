
#ifndef CB_INTEGER_H
#define CB_INTEGER_H

extern Class IntegerClass;

typedef struct _CBInteger {
	OBJECT_BASE
	
	int value;
} *Integer;

void integer_class_init();

#endif
