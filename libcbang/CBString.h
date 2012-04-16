
#ifndef CB_STRING_H
#define CB_STRING_H

extern Class StringClass;

typedef struct _CBString {
	OBJECT_BASE
	
	string value;
} *String;

void string_class_init();

#endif
