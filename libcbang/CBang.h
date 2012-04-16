
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#include "list.h"

#ifndef CBANG_H
#define CBANG_H

typedef struct _method *method;

typedef unsigned int uint;
typedef char *string;
typedef void *(*fpointer) (void *v, va_list *args);
typedef void *(*spointer) (void *v);

typedef struct _CBClass *Class;

struct _method {
	string name;
	fpointer function;
};

void cbang_init();
void *message(void *v, string message, ...);
void destruct(void *v);

method mmethod(string name, fpointer function);

string mstring(string s);

#endif

#include "CBObject.h"
#include "CBClass.h"
#include "CBNull.h"
#include "CBString.h"
#include "CBInteger.h"
#include "CBStack.h"
#include "CBFile.h"
#include "CBScanner.h"
