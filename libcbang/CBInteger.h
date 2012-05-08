
#ifndef CB_INTEGER_H
#define CB_INTEGER_H

extern Class IntegerClass;

typedef struct _CBInteger {
	struct _CBObject base;	
	size_t value;
} *Integer;

void integer_class_init();

#endif
