
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#include "list.h"

#ifndef CBANG_H
#define CBANG_H

typedef struct _class *class;
typedef struct _method *method;

typedef unsigned int uint;
typedef char *string;
typedef void *(*cpointer) (void *v, void **p, va_list *args);
typedef void (*dpointer) (void *v);
typedef void *(*spointer) (void *v);
typedef void *(*fpointer) (void *v, va_list *args);

struct _class {
	class parent;
	string name;
	cpointer constructor;
	dpointer destructor;
	spointer super;
	list *methods;
};

struct _method {
	string name;
	fpointer function;
};

void cbang_init();
void add_class(class);
void *construct(string class_name, ...);
void *message(void *v, string message, ...);
void destruct(void *v);

class mclass(string name, string parent_class_name, cpointer constructor, dpointer destructor, spointer super);
method mmethod(string name, fpointer function);

string mstring(string s);

#endif

#include "CBObject.h"
#include "CBNull.h"
#include "CBString.h"
#include "CBInteger.h"
#include "CBStack.h"
