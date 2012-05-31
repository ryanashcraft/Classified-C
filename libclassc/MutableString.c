
#include "Classified-C.h"

IMPLEMENTATION(MutableStringClass);

PROTOTYPE(newWithCString);
PROTOTYPE(newWithCStringAndCapacity);
PROTOTYPE(initWithCString);
PROTOTYPE(initWithCStringAndCapacity);
PROTOTYPE(dealloc);
PROTOTYPE(concatenateWithCString);
PROTOTYPE(concatenateWithString);
PROTOTYPE(appendCharacter);
PROTOTYPE(vsprint);

static cstring concatenate(MutableString s, cstring part_two);
static void virtual_vsprintf(char *, va_list *args);

void mutable_string_class_init() {
	MutableStringClass = msg(ClassClass, "new", "MutableString", StringClass);

	REGISTER_CLASS_METHOD(MutableStringClass, "newWithCString", newWithCString);
	REGISTER_CLASS_METHOD(MutableStringClass, "newWithCStringAndCapacity", newWithCStringAndCapacity);

	REGISTER_METHOD(MutableStringClass, "initWithCString", initWithCString);
	REGISTER_METHOD(MutableStringClass, "initWithCStringAndCapacity", initWithCStringAndCapacity);
	REGISTER_METHOD(MutableStringClass, "dealloc", dealloc);
	REGISTER_METHOD(MutableStringClass, "concatenateWithCString", concatenateWithCString);
	REGISTER_METHOD(MutableStringClass, "concatenateWithString", concatenateWithString);
	REGISTER_METHOD(MutableStringClass, "appendCharacter", appendCharacter);
	REGISTER_METHOD(MutableStringClass, "vsprint", vsprint);
}

DEFINE(newWithCString) {
	NEW(MutableStringClass, struct _MutableString);

	initWithCString(self, args);

	return self;
}

DEFINE(newWithCStringAndCapacity) {
	NEW(MutableStringClass, struct _MutableString);

	initWithCStringAndCapacity(self, args);

	return self;
}

DEFINE(initWithCString) {
	CONTEXT(MutableString);

	msg_cast(StringClass, self, "initWithCString", NEXT_ARG(cstring));
	self->capacity = strlen(self->base.value);

	return self;
}

DEFINE(initWithCStringAndCapacity) {
	CONTEXT(MutableString);

	msg_cast(StringClass, self, "initWithCString", NEXT_ARG(cstring));

	self->capacity = NEXT_ARG(int);
	int string_length = strlen(self->base.value);
	self->base.value = realloc(self->base.value, self->capacity);
	self->base.value[string_length] = '\0';

	return self;
}

DEFINE(dealloc) {
	CONTEXT(MutableString);

	return msg_cast(StringClass, self, "dealloc");
}

DEFINE(concatenateWithCString) {
	CONTEXT(MutableString);

	cstring part_two = NEXT_ARG(cstring);
	self->base.value = concatenate(self, part_two);

	return self;
}

DEFINE(concatenateWithString) {
	CONTEXT(MutableString);

	String stringArgument = NEXT_ARG(String);
	cstring part_two = stringArgument->value;
	self->base.value = concatenate(self, part_two);

	return self;
}

cstring concatenate(MutableString self, cstring part_two) {
	int part_one_length = strlen(self->base.value);
	int part_two_length = strlen(part_two);

	if (part_one_length + part_two_length + 1 > self->capacity) {
		self->base.value = realloc(self->base.value, self->capacity * 2 + part_two_length + 1);
		assert(self->base.value);
	}
 	
	strncat(self->base.value, part_two, part_two_length);

	return self->base.value;
}

DEFINE(appendCharacter) {
	CONTEXT(MutableString);

	char c = NEXT_ARG(int);

	int string_length = strlen(self->base.value);

	if (string_length + 2 >= self->capacity) {
		self->capacity *= 2;
		self->base.value = realloc(self->base.value, self->capacity);
		assert(self->base.value);
	}

	self->base.value[string_length] = c;
	self->base.value[string_length + 1] = '\0';

	return self;
}

DEFINE(vsprint) {
	CONTEXT(MutableString);

	cstring dup = mstring(self->base.value);

	va_list *format_args = NEXT_ARG(va_list *);
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
}

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
					NEXT_ARG(int);
					break;
				case 'f':
				case 'e':
				case 'E':
				case 'g':
				case 'G':
					NEXT_ARG(double);
					break;
				case 's':
					break;
				case 'p':
				case 'n':
					NEXT_ARG(char *);
					break;
			}
		}
	}
}
