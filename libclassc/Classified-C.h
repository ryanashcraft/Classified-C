
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#include "list.h"
#include "hashtable/hashtable.h"

#define CAT_CLASS(A) A ## Class
#define EXP_CLASS(A) CAT_CLASS(A)
#define CLASS_REF EXP_CLASS(CLASS)

#define NAME EXP_STR(CLASS)

#define CAT_STRUCT(A) struct _ ## A
#define EXP_STRUCT(A) CAT_STRUCT(A)
#define STRUCT EXP_STRUCT(CLASS)

#define CAT_INIT(A) A ## Init
#define EXP_INIT(A) CAT_INIT(A)
#define CLASS_INIT EXP_INIT(CLASS)

#ifndef SUPER_CLASS_REF
#define SUPER_CLASS_REF EXP_CLASS(SUPER)
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
	Class CLASS_REF = NULL; \
	void CLASS_INIT() { \
		CLASS_REF = msg(ClassClass, "new", NAME, SUPER_CLASS_REF);

#define defcon(METHOD) \
	void *METHOD(METHOD_ARGS) { \
		STRUCT *self = cc_alloc(sizeof(STRUCT)); \
		object_init(self); \
		((Object)self)->root = CLASS_REF;

#define def(METHOD) \
	void *METHOD(METHOD_ARGS) { \
		CLASS self = (CLASS)v; \
		(void)self;

#define end }

#define instance(FUNCTION) \
	ht_insert_method(&CLASS_REF->instance_methods, #FUNCTION, strlen(#FUNCTION), mmethod(#FUNCTION, &FUNCTION), sizeof(struct _method));

#define static(FUNCTION) \
	ht_insert_method(&CLASS_REF->static_methods, #FUNCTION, strlen(#FUNCTION), mmethod(#FUNCTION, &FUNCTION), sizeof(struct _method));

#define NEXT_ARG(CLASS) va_arg(*args, CLASS)
#define ARGS args

#define msgSuper(...) msgCast(SUPER_CLASS_REF, self, __VA_ARGS__)

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
void *msgCast(Class c, void *v, cstring message, ...);

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
