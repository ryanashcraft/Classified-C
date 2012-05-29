
#ifndef CB_STRING_H
#define CB_STRING_H

extern Class StringClass;

typedef struct _CBString {
	struct _CBObject base;
	cstring value;
} *String;

void string_class_init();

#endif
