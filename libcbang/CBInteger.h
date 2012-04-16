
#ifndef CB_INTEGER_H
#define CB_INTEGER_H

extern Class IntegerClass;

typedef struct _CBInteger {
	Class class;
	list *methods;
	Object parent;
	
	int value;
} *Integer;

void integer_class_init();

#endif
