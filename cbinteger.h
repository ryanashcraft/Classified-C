
#ifndef CB_INTEGER_H
#define CB_INTEGER_H

typedef struct _CBInteger {
	struct _obj meta;
	int value;
} *CBInteger;

int cbinteger_to_int();

class cbinteger_init();

#endif