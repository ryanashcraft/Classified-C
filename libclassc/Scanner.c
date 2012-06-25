
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

	String token = msg(buffer, "copy");
	msg(buffer, "release");

	return msg(token, "autorelease");
end

def(hasNext)
	FILE *f = msg(self->file, "file");
	boolean hasNext = YES;
	char c = 0;

	c = fgetc(f);
	if (c == EOF) {
		hasNext = NO;
	}
	ungetc(c, f);

	return hasNext;
end
