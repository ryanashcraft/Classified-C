
#ifndef OBJC_H
#define OBJC_H

#include "list.h"

typedef struct _class class;
typedef struct _obj obj;
typedef struct _method method;

typedef obj * var;

typedef unsigned int uint;
typedef char * string;
typedef obj * (*cpointer) (void);
typedef obj * (*fpointer) (var obj);

struct _class {
	string name;
	cpointer constructor;
	list *v_table;
};

struct _obj {
	class *class;
};

struct _method {
	string name;
	fpointer f_pointer;
};

void _objc_init();
var objc_constructor(string class_name);
var objc_message_send(var o, string message);

#endif