
#ifndef CB_STRING_H
#define CB_STRING_H

extern Class StringClass;

typedef struct _CBString {
	Class class;
	list *methods;
	string value;
	struct _CBObject parent;
} *String;

void string_class_init();

#endif
