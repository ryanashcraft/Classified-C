
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#include "list.h"

#ifndef CBANG_H
#define CBANG_H

typedef char *cstring;
typedef void *(*fpointer) (void *v, va_list *args);
typedef struct _CBObject *Object;
typedef struct _CBClass *Class;
typedef size_t *boolean;

typedef struct _method {
	cstring name;
	fpointer function;
} *method;

extern Object SystemOut;

void cbinit();
void *msg(void *v, cstring message, ...);
void *msg_cast(Class c, void *v, cstring message, ...);

void *cballoc(size_t size);

method mmethod(cstring name, fpointer function);
cstring mstring(cstring s);

#endif

#include "CBObject.h"
#include "CBClass.h"
#include "CBNull.h"
#include "CBString.h"
#include "CBMutableString.h"
#include "CBInteger.h"
#include "CBStack.h"
#include "CBFile.h"
#include "CBScanner.h"
#include "CBPrinter.h"

#define YES ((size_t *)1)
#define NO ((size_t *)0)