
#ifndef INTEGER_H
#define INTEGER_H

extern Class IntegerClass;

typedef struct _Integer {
	struct _Object base;	
	int value;
} *Integer;

void IntegerInit();
int to_int(Integer);

#endif
