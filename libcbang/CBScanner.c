
#include "CBang.h"
#include "CBScanner.h"

#define TOKEN_BUFFER_SIZE 256

Class ScannerClass = NULL;

typedef struct _CBScanner {
	OBJECT_BASE
	
	var file;
} *Scanner;

static void *initWithFile(void *v, va_list *args);

static void *dealloc(void *v, va_list *args);
static void *next(void *v, va_list *args);
static void *has_next(void *v, va_list *args);

void scanner_class_init() {
	ScannerClass = msg(ClassClass, "init", "Scanner", ObjectClass);

	push_back(ScannerClass->methods, mmethod("initWithFile", &initWithFile));

	push_back(ScannerClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(ScannerClass->instance_methods, mmethod("next", &next));
	push_back(ScannerClass->instance_methods, mmethod("has_next", &has_next));
}

void *initWithFile(void *v, va_list *args) {
	Scanner o;

	o = calloc(1, sizeof(struct _CBScanner));
	assert(o);

	Object root = va_arg(*args, Object);
	if (!root) {
		root = (Object)o;
	}

	o->class = ScannerClass;
	o->methods = ScannerClass->instance_methods;
	o->parent = msg(ObjectClass, "init", root);
	o->root = root;

	o->file = va_arg(*args, var);

	return o;
}

void *dealloc(void *v, va_list *args) {
	Scanner o = (Scanner)v;
	msg(o->parent, "dealloc");
	free(o);
	return NULL;
}

void *next(void *v, va_list *args) {
	Scanner o = (Scanner)v;
	FILE *f = msg(o->file, "file");

	string buffer = calloc(1, TOKEN_BUFFER_SIZE);
	assert(buffer);
	char c;
	int i;

	i = 0;
	getcloop:
    do {
		c = fgetc(f);

		if (c == EOF || c < 33) {
			if (i == 0) {
				goto getcloop;
			}

			break;
		}
		
		buffer[i] = c;
	} while (++i);

	var token = msg(StringClass, "initWithString", NULL, buffer);

	free(buffer);

	return token;
}

void *has_next(void *v, va_list *args) {
	Scanner o = (Scanner)v;
	FILE *f = msg(o->file, "file");
	int has_next = 1;
	char c = 0;

	c = fgetc(f);
	if (c == EOF) {
		has_next = 0;
	}
	ungetc(c, f);

	var retval = msg(IntegerClass, "initWithInt", NULL, has_next);

	return retval;
}
