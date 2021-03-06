
#define CLASS String
#define SUPER Object

#include "Classified-C.h"

#define START_FORMAT_BUFFER_SIZE 32

proto(newWithCString);
proto(newWithFormatCString);
proto(newWithFormatCStringAndArgList);
proto(initWithCString);
proto(initWithFormatCString);
proto(initWithFormatCStringAndArgList);
proto(dealloc);
proto(copy);
proto(length);
proto(description);
proto(equals);
proto(cString);

static cstring format(cstring format, va_list *format_args);

defclass {
	constructor(newWithCString);
	constructor(newWithFormatCString);
	constructor(newWithFormatCStringAndArgList);

	instance(initWithCString);
	instance(initWithFormatCString);
	instance(initWithFormatCStringAndArgList);
	instance(dealloc);
	instance(copy);
	instance(length);
	instance(description);
	instance(equals);
	instance(cString)
} end

defcon(newWithCString) {
	initWithCString(self, args);

	return self;
} end

defcon(newWithFormatCString) {
	initWithFormatCString(self, args);

	return self;
} end

defcon(newWithFormatCStringAndArgList) {
	initWithFormatCStringAndArgList(self, args);

	return self;
} end

def(initWithCString) {
	cstring string_arg = nextArg(cstring);
	self->value = mstring(string_arg);

	return self;
} end

def(initWithFormatCString) {
	cstring formatString = nextArg(cstring);
	self->value = format(formatString, args);

	return self;
} end

def(initWithFormatCStringAndArgList) {
	cstring formatString = nextArg(cstring);
	va_list *formatArgList = nextArg(va_list *);
	self->value = format(formatString, formatArgList);

	return self;
} end

static cstring format(cstring format, va_list *format_args) {
	int format_length = strlen(format);
	MutableString buffer = msg(MutableStringClass, "newWithCStringAndCapacity", "", START_FORMAT_BUFFER_SIZE);

	Boolean needsFinalVSprint = NO;
	for (int i = 0; i < format_length; i++) {
		if (i <= format_length && (format[i] == '%' && format[i + 1] == '@')) {
			msg(buffer, "vsprint", format_args);
			Object objectArgument = va_arg(*format_args, Object);
			String objectDescription = msg(objectArgument, "description");
			msg(buffer, "concatenateWithCString", objectDescription->value);
			i++;
			needsFinalVSprint = NO;
		} else {
			msg(buffer, "appendCharacter", format[i]);

			if (i <= format_length && (format[i] == '%' && format[i + 1] != '%')) {
				needsFinalVSprint = YES;
			}
		}
	}

	if (needsFinalVSprint) {
		msg(buffer, "vsprint", format_args);
	}

	cstring formatted_string = mstring(buffer->base.value);
	msg(buffer, "release");

	return formatted_string;;
}

def(dealloc) {
	free(self->value);

	return msgSuper("dealloc");
} end

def(copy) {
	return msg(StringClass, "newWithCString", self->value);
} end

def(length) {
	Integer length = msg(IntegerClass, "newWithInt", strlen(self->value));

	return msg(length, "autoRelease");
} end

def(description) {
	return msg(copy(v, args), "autoRelease");
} end

def(equals) {
	cstring other = nextArg(cstring);

	int length = strlen(self->value);
	int other_length = strlen(other);
	if (length != other_length) {
		return NO;
	}

	if (strncmp(self->value, other, strlen(self->value)) == 0) {
		return YES;
	}
	
	return NO;
} end

def(cString) {
	return self->value;
} end
