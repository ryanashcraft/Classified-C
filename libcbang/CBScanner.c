
#include "CBang.h"
#include "CBScanner.h"

#define TOKEN_BUFFER_SIZE 256

Class ScannerClass = NULL;

static void *initWithFile(void *v, va_list *args);

static void *release(void *v, va_list *args);
static void *next(void *v, va_list *args);
static void *has_next(void *v, va_list *args);

void scanner_class_init() {
	method m;

	ScannerClass = message(ClassClass, "init", "ScannerClass", ObjectClass);

	m = mmethod("initWithFile", &initWithFile);
	push_back(ScannerClass->methods, m);
}

void *initWithFile(void *v, va_list *args) {
	Scanner s;
	method m;

	s = calloc(1, sizeof(struct _CBScanner));
	assert(s);

	s->class = ScannerClass;
	s->file = va_arg(*args, File);

	s->methods = create_list();
	m = mmethod("release", &release);
	push_back(s->methods, m);
	m = mmethod("next", &next);
	push_back(s->methods, m);
	m = mmethod("has_next", &has_next);
	push_back(s->methods, m);

	s->parent = message(ObjectClass, "init");

	return s;
}

void *release(void *v, va_list *args) {
	Scanner s = (Scanner)v;
	message(s->parent, "release");
	free_list(s->methods, &free);
	free(s);
	return s;
}

void *next(void *v, va_list *args) {
	Scanner s = (Scanner)v;
	FILE *f = s->file->file;

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

	String token = message(StringClass, "initWithString", buffer);

	free(buffer);

	return token;
}

void *has_next(void *v, va_list *args) {
	Scanner s = (Scanner)v;
	FILE *f = s->file->file;
	int has_next = 1;
	char c = 0;

	c = fgetc(f);
	if (c == EOF) {
		has_next = 0;
	}
	ungetc(c, f);

	Integer retval = message(IntegerClass, "initWithInt", has_next);

	return retval;
}
