
#ifndef INTEGER_H
#define INTEGER_H

extern Class IntegerClass;

typedef struct _Integer {
	struct _Object base;	
	size_t value;
} *Integer;

void IntegerInit();

#endif
