
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#include "list.h"
#include "hashtable/hashtable.h"

#define CAT_CLASS(A) A ## Class
#define EXP_CLASS(A) CAT_CLASS(A)
#define CLASS EXP_CLASS(TYPE)

#define NAME EXP_STR(TYPE)

#define CAT_STRUCT(A) struct _ ## A
#define EXP_STRUCT(A) CAT_STRUCT(A)
#define STRUCT EXP_STRUCT(TYPE)

#define CAT_INIT(A) A ## Init
#define EXP_INIT(A) CAT_INIT(A)
#define CLASS_INIT EXP_INIT(TYPE)

#ifndef SUPER_CLASS
#define SUPER_CLASS EXP_CLASS(SUPER)
#endif

#ifndef CLASSIFIEDC_H
#define CLASSIFIEDC_H

#define STR(A) #A

#define EXP_STR(A) STR(A)

#define proto(NAME) \
	static void *NAME(METHOD_ARGS)

#define METHOD_ARGS \
	void *v, va_list *args

#define defclass \
	Class CLASS = NULL; \
	void CLASS_INIT() { \
		CLASS = msg(ClassClass, "new", NAME, SUPER_CLASS);

#define defcon(METHOD) \
	void *METHOD(METHOD_ARGS) { \
		STRUCT *self = cc_alloc(sizeof(STRUCT)); \
		object_init(self); \
		((Object)self)->root = CLASS;

#define def(METHOD) \
	void *METHOD(METHOD_ARGS) { \
		TYPE self = (TYPE)v; \
		(void)self;

#define end }

#define instance(FUNCTION) \
		ht_insert_method(&CLASS->instance_methods, #FUNCTION, strlen(#FUNCTION), mmethod(#FUNCTION, &FUNCTION), sizeof(struct _method));

#define static(FUNCTION) \
		ht_insert_method(&CLASS->static_methods, #FUNCTION, strlen(#FUNCTION), mmethod(#FUNCTION, &FUNCTION), sizeof(struct _method));

#define NEXT_ARG(TYPE) va_arg(*args, TYPE)
#define ARGS args

#define YES (void *)1
#define NO (void *)0

typedef char *cstring;
typedef void *(*fpointer) (void *v, va_list *args);
typedef struct _Object *Object;
typedef struct _Class *Class;
typedef size_t *boolean;

typedef struct _method {
	cstring name;
	fpointer function;
} method;

extern Object SystemOut;

void cc_init();
void *msg(void *v, cstring message, ...);
void *msg_cast(Class c, void *v, cstring message, ...);

void *cc_alloc(size_t size);
void msg_release(void *v);

method *mmethod(cstring name, fpointer function);
void dmethod(method *m);
cstring mstring(cstring s);

void ht_insert_method(hashtable **table, void *key, size_t key_size, void *value, size_t value_size);

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
