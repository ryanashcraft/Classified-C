
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#include "list.h"

#ifndef CLASSIFIEDC_H
#define CLASSIFIEDC_H

#define IMPLEMENTATION(CLASS) Class CLASS = NULL
#define PROTOTYPE(NAME) static void *NAME(METHOD_ARGS)
#define METHOD_ARGS void *v, va_list *args
#define DEFINE(NAME) void *NAME(METHOD_ARGS)
#define NEW(CLASS_REF, STRUCT) STRUCT *self = cc_alloc(sizeof(STRUCT)); object_init(self); ((Object)self)->root = CLASS_REF;
#define CONTEXT(CLASS) CLASS self = (CLASS)v;
#define REGISTER_METHOD(CLASS, NAME, FUNCTION) push_back(CLASS->instance_methods, mmethod(NAME, &FUNCTION));
#define REGISTER_CLASS_METHOD(CLASS, NAME, FUNCTION) push_back(CLASS->static_methods, mmethod(NAME, &FUNCTION));
#define NEXT_ARG(TYPE) va_arg(*args, TYPE)
#define ARGS args

#define YES msg(BooleanClass, "yes")
#define NO msg(BooleanClass, "no")

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
void msg_release(void *v);

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
#include "Boolean.h"
#include "Stack.h"
#include "File.h"
#include "Scanner.h"
#include "Printer.h"
#include "Iterator.h"
#include "LinkedList.h"
