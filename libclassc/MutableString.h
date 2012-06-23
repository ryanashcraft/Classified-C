
#ifndef MUTABLE_STRING_H
#define MUTABLE_STRING_H

extern Class MutableStringClass;

typedef struct _MutableString {
	struct _String base;
	int capacity;
} *MutableString;

void MutableStringInit();

#endif
