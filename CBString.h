
#ifndef CB_STRING_H
#define CB_STRING_H

#include "CBObject.h"

typedef struct _CBString {
	class type;
	string value;
	struct _CBObject parent;
} *CBString;

class cbstring_init();

#endif