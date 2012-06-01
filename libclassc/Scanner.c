
#include "Classified-C.h"

#define TOKEN_BUFFER_SIZE 256

IMPLEMENTATION(ScannerClass);

PROTOTYPE(newWithFile);
PROTOTYPE(initWithFile);
PROTOTYPE(dealloc);
PROTOTYPE(next);
PROTOTYPE(hasNext);

void scanner_class_init() {
	ScannerClass = msg(ClassClass, "new", "Scanner", ObjectClass);

	REGISTER_CLASS_METHOD(ScannerClass, "newWithFile", newWithFile);

	REGISTER_METHOD(ScannerClass, "initWithFile", initWithFile);
	REGISTER_METHOD(ScannerClass, "dealloc", dealloc);
	REGISTER_METHOD(ScannerClass, "next", next);
	REGISTER_METHOD(ScannerClass, "hasNext", hasNext);
}

DEFINE(newWithFile) {
	NEW(ScannerClass, struct _Scanner);

	initWithFile(self, args);

	return self;
}

DEFINE(initWithFile) {
	CONTEXT(Scanner);

	self->file = NEXT_ARG(File);

	return self;
}

DEFINE(dealloc) {
	CONTEXT(Scanner);

	return msg_cast(ObjectClass, self, "dealloc");
}

DEFINE(next) {
	CONTEXT(Scanner);

	FILE *f = msg(self->file, "file");
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

DEFINE(hasNext) {
	CONTEXT(Scanner);

	FILE *f = msg(self->file, "file");
	int has_next = 1;
	char c = 0;

	c = fgetc(f);
	if (c == EOF) {
		has_next = 0;
	}
	ungetc(c, f);

	Integer hasNext = msg(IntegerClass, "newWithInt", has_next);

	return hasNext;
}
