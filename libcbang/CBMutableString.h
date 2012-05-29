
#ifndef CB_MUTABLE_STRING_H
#define CB_MUTABLE_STRING_H

extern Class MutableStringClass;

typedef struct _CBMutableString {
	struct _CBString base;
	int capacity;
} *MutableString;

void mutable_string_class_init();

#endif
