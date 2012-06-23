
#define CLASS Scanner
#define SUPER Object

#include "Classified-C.h"

#define TOKEN_BUFFER_SIZE 256

proto(newWithFile);
proto(initWithFile);
proto(next);
proto(hasNext);

defclass
	static(newWithFile);

	instance(initWithFile);
	instance(next);
	instance(hasNext);
end

defcon(newWithFile)
	initWithFile(self, args);

	return self;
end

def(initWithFile)
	self->file = NEXT_ARG(File);

	return self;
end

def(next)
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
end

def(hasNext)
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
end
