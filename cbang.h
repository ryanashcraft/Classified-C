
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#include "list.h"

#ifndef CBANG_H
#define CBANG_H

typedef struct _class *class;
typedef struct _obj *var;
typedef struct _method *method;

typedef unsigned int uint;
typedef char *string;
typedef var (*cpointer) (va_list args);
typedef void (*dpointer) (var v);
typedef var (*fpointer) (var v, va_list args);

struct _class {
	class parent;
	string name;
	cpointer constructor;
	dpointer destructor;
	list *methods;
};

struct _obj {
	var parent;
	class type;
	void *data;
};

struct _method {
	string name;
	fpointer function;
};

void cbang_init();
void add_class(class);
var construct(string class_name, ...);
var message(var v, string message, ...);
void destruct(var v);

class mclass(string name, string parent_class_name, cpointer constructor, dpointer destructor);
method mmethod(string name, fpointer function);
var mvar(class class);

string mstring(string s);

#endif