
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#include "list.h"

#ifndef CLASSIFIEDC_H
#define CLASSIFIEDC_H

typedef char *cstring;
typedef void *(*fpointer) (void *v, va_list *args);
typedef struct _Object *Object;
typedef struct _Class *Class;
typedef size_t *boolean;

typedef struct _method {
	cstring name;
	fpointer function;
} *method;

extern Object SystemOut;

void cc_init();
void *msg(void *v, cstring message, ...);
void *msg_cast(Class c, void *v, cstring message, ...);

void *cc_alloc(size_t size);

method mmethod(cstring name, fpointer function);
cstring mstring(cstring s);

#endif

#include "Object.h"
#include "Class.h"
#include "Null.h"
#include "Array.h"
#include "String.h"
#include "MutableString.h"
#include "Integer.h"
#include "Stack.h"
#include "File.h"
#include "Scanner.h"
#include "Printer.h"
#include "Iterator.h"

#define YES ((size_t *)1)
#define NO ((size_t *)0)
