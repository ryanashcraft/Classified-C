
#ifndef STRING_H
#define STRING_H

extern Class StringClass;

typedef struct _String {
	struct _Object base;
	cstring value;
} *String;

void string_class_init();

#endif
