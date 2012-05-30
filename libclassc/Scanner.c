
#include "Classified-C.h"

#define TOKEN_BUFFER_SIZE 256

Class ScannerClass = NULL;

static void *newWithFile(void *v, va_list *args);

static void *initWithFile(void *v, va_list *args);
static void *dealloc(void *v, va_list *args);
static void *next(void *v, va_list *args);
static void *has_next(void *v, va_list *args);

void scanner_class_init() {
	ScannerClass = msg(ClassClass, "new", "Scanner", ObjectClass);

	push_back(ScannerClass->static_methods, mmethod("newWithFile", &newWithFile));

	push_back(ScannerClass->instance_methods, mmethod("initWithFile", &initWithFile));
	push_back(ScannerClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(ScannerClass->instance_methods, mmethod("next", &next));
	push_back(ScannerClass->instance_methods, mmethod("has_next", &has_next));
}

void *newWithFile(void *v, va_list *args) {
	Scanner o = cc_alloc(sizeof(struct _Scanner));
	initWithFile(o, args);
	((Object)o)->root = ScannerClass;
	return o;
}

void *initWithFile(void *v, va_list *args) {
	Scanner o = (Scanner)v;
	msg_cast(ObjectClass, o, "init");
	o->file = va_arg(*args, File);
	return o;
}

void *dealloc(void *v, va_list *args) {
	Scanner o = (Scanner)v;
	return msg_cast(ObjectClass, o, "dealloc");
}

void *next(void *v, va_list *args) {
	Scanner o = (Scanner)v;
	FILE *f = msg(o->file, "file");

	MutableString buffer = msg(MutableStringClass, "newWithCStringAndCapacity", "", TOKEN_BUFFER_SIZE);

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
		
		msg(buffer, "appendCharacter", c);
	} while (++i);

	String token = msg_cast(StringClass, buffer, "copy");
	msg(buffer, "release");

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

	Integer retval = msg(IntegerClass, "newWithInt", has_next);

	return retval;
}