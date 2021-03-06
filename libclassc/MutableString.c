
#define CLASS MutableString
#define SUPER String

#include "Classified-C.h"

proto(newWithCString);
proto(newWithCStringAndCapacity);
proto(initWithCString);
proto(initWithCStringAndCapacity);
proto(dealloc);
proto(concatenateWithCString);
proto(concatenateWithString);
proto(appendCharacter);
proto(vsprint);

static cstring concatenate(MutableString s, cstring part_two);
static void virtual_vsprintf(char *, va_list *args);

defclass {
	constructor(newWithCString);
	constructor(newWithCStringAndCapacity);

	instance(initWithCString);
	instance(initWithCStringAndCapacity);
	instance(dealloc);
	instance(concatenateWithCString);
	instance(concatenateWithString);
	instance(appendCharacter);
	instance(vsprint);
} end

defcon(newWithCString) {
	initWithCString(self, args);

	return self;
} end

defcon(newWithCStringAndCapacity) {
	initWithCStringAndCapacity(self, args);

	return self;
} end

def(initWithCString) {
	msgSuper("initWithCString", nextArg(cstring));
	self->capacity = strlen(self->base.value);

	return self;
} end

def(initWithCStringAndCapacity) {
	msgSuper("initWithCString", nextArg(cstring));

	self->capacity = nextArg(int);
	int string_length = strlen(self->base.value);
	self->base.value = realloc(self->base.value, self->capacity);
	self->base.value[string_length] = '\0';

	return self;
} end

def(dealloc) {
	return msgSuper("dealloc");
} end

def(concatenateWithCString) {
	cstring part_two = nextArg(cstring);
	self->base.value = concatenate(self, part_two);

	return self;
} end

def(concatenateWithString) {
	String stringArgument = nextArg(String);
	cstring part_two = stringArgument->value;
	self->base.value = concatenate(self, part_two);

	return self;
} end

cstring concatenate(MutableString self, cstring part_two) {
	int part_one_length = strlen(self->base.value);
	int part_two_length = strlen(part_two);

	if (part_one_length + part_two_length + 1 > self->capacity) {
		self->capacity = (self->capacity * 2) + part_two_length + 1;
		self->base.value = realloc(self->base.value, self->capacity);
		assert(self->base.value);
	}
 	
	strncat(self->base.value, part_two, part_two_length);

	return self->base.value;
}

def(appendCharacter) {
	char c = nextArg(int);

	int string_length = strlen(self->base.value);

	if (string_length + 2 >= self->capacity) {
		self->capacity *= 2;
		self->base.value = realloc(self->base.value, self->capacity);
		assert(self->base.value);
	}

	self->base.value[string_length] = c;
	self->base.value[string_length + 1] = '\0';

	return self;
} end

def(vsprint) {
	cstring dup = mstring(self->base.value);

	va_list *format_args = nextArg(va_list *);
	va_list duplicate_format_args;
	va_copy(duplicate_format_args, *format_args);
	size_t required = vsnprintf(NULL, 0, dup, duplicate_format_args);
	va_end(duplicate_format_args);
	if (required >= self->capacity) {
		self->capacity += required;
		self->base.value = realloc(self->base.value, self->capacity);
		assert(self->base.value);
	}
	va_copy(duplicate_format_args, *format_args);
	vsprintf(self->base.value, dup, duplicate_format_args);
	va_end(duplicate_format_args);

	virtual_vsprintf(dup, format_args);

	free(dup);

	int string_length = strlen(self->base.value);
	self->base.value[string_length] = '\0';

	return self;
} end

void virtual_vsprintf(char *format, va_list *args) {
	const char *p = format;

	while (*p != '\0') {
		if (*p++ == '%') {
			while (strchr("-+ #0", *p)) {
				++p;
			}

			if (*p == '*') {
				++p;
			}

			if (*p == '.') {
	      		++p;
	      		if (*p == '*') {
	      			++p;
				}
			}

			while (strchr("hlL", *p)) {
				++p;
			}

			switch (*p) {
				case 'd':
				case 'i':
				case 'o':
				case 'u':
				case 'x':
				case 'X':
				case 'c':
					nextArg(int);
					break;
				case 'f':
				case 'e':
				case 'E':
				case 'g':
				case 'G':
					nextArg(double);
					break;
				case 's':
					break;
				case 'p':
				case 'n':
					nextArg(char *);
					break;
			}
		}
	}
}
