
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#include "list.h"

#ifndef CBANG_H
#define CBANG_H

typedef char *string;
typedef void *(*fpointer) (void *v, va_list *args);
typedef void *(*spointer) (void *v);
typedef struct _CBClass *Class;
typedef size_t *boolean;

typedef struct _CBObject *var;

typedef struct _method {
	string name;
	fpointer function;
} *method;

void cbang_init();
void *msg(void *v, string message, ...);

void *cballoc(size_t size);

method mmethod(string name, fpointer function);
string mstring(string s);

#endif

#include "CBObject.h"
#include "CBClass.h"
#include "CBNull.h"
#include "CBString.h"
// #include "CBInteger.h"
// #include "CBStack.h"
// #include "CBFile.h"
// #include "CBScanner.h"

#define YES ((size_t *)1)
#define NO ((size_t *)0)