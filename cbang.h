
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#include "list.h"

#ifndef CBANG_H
#define CBANG_H

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
	list *methods;
};

struct _obj {
	class *class;
};

struct _method {
	string name;
	fpointer function;
};

void cbang_init();
var cbang_constructor(string class_name);
var cbang_message_send(var o, string message);

class *mclass(string name, cpointer constructor);
method *mmethod(string name, fpointer function);
obj *mvar(class *class);

string mstring(string s);

#endif