
#include "Classified-C.h"

#define START_FORMAT_BUFFER_SIZE 32

IMPLEMENTATION(StringClass);

PROTOTYPE(newWithCString);
PROTOTYPE(newWithFormatCString);
PROTOTYPE(newWithFormatCStringAndArgList);
PROTOTYPE(initWithCString);
PROTOTYPE(initWithFormatCString);
PROTOTYPE(initWithFormatCStringAndArgList);
PROTOTYPE(dealloc);
PROTOTYPE(copy);
PROTOTYPE(length);
PROTOTYPE(description);
PROTOTYPE(equals);

static cstring format(cstring format, va_list *format_args);

void string_class_init() {
	StringClass = msg(ClassClass, "new", "String", ObjectClass);

	REGISTER_CLASS_METHOD(StringClass, "newWithCString", newWithCString);
	REGISTER_CLASS_METHOD(StringClass, "newWithFormatCString", newWithFormatCString);
	REGISTER_CLASS_METHOD(StringClass, "newWithFormatCStringAndArgList", newWithFormatCStringAndArgList);

	REGISTER_METHOD(StringClass, "initWithCString", initWithCString);
	REGISTER_METHOD(StringClass, "initWithFormatCString", initWithFormatCString);
	REGISTER_METHOD(StringClass, "initWithFormatCStringAndArgList", initWithFormatCStringAndArgList);
	REGISTER_METHOD(StringClass, "dealloc", dealloc);
	REGISTER_METHOD(StringClass, "copy", copy);
	REGISTER_METHOD(StringClass, "length", length);
	REGISTER_METHOD(StringClass, "description", description);
	REGISTER_METHOD(StringClass, "equals", equals);
}

DEFINE(newWithCString) {
	NEW(StringClass, struct _String);

	initWithCString(self, args);

	return self;
}

DEFINE(newWithFormatCString) {
	NEW(StringClass, struct _String);

	initWithFormatCString(self, args);

	return self;
}

DEFINE(newWithFormatCStringAndArgList) {
	NEW(StringClass, struct _String);

	initWithFormatCStringAndArgList(self, args);

	return self;
}

DEFINE(initWithCString) {
	CONTEXT(String);

	cstring string_arg = NEXT_ARG(cstring);
	self->value = mstring(string_arg);

	return self;
}

DEFINE(initWithFormatCString) {
	CONTEXT(String);

	cstring formatString = NEXT_ARG(cstring);
	self->value = format(formatString, args);

	return self;
}

DEFINE(initWithFormatCStringAndArgList) {
	CONTEXT(String);

	cstring formatString = NEXT_ARG(cstring);
	va_list *formatArgList = NEXT_ARG(va_list *);
	self->value = format(formatString, formatArgList);

	return self;
}

static cstring format(cstring format, va_list *format_args) {
	int format_length = strlen(format);
	MutableString buffer = msg(MutableStringClass, "newWithCStringAndCapacity", "", START_FORMAT_BUFFER_SIZE);

	boolean needsFinalVSprint = NO;
	for (int i = 0; i < format_length; i++) {
		if (i <= format_length && (format[i] == '%' && format[i + 1] == '@')) {
			msg(buffer, "vsprint", format_args);
			Object objectArgument = va_arg(*format_args, Object);
			String objectDescription = msg(objectArgument, "description");
			msg(buffer, "concatenateWithCString", objectDescription->value);
			msg(objectDescription, "release");
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

DEFINE(dealloc) {
	CONTEXT(String);

	free(self->value);

	return msg_cast(ObjectClass, self, "dealloc");
}

DEFINE(copy) {
	CONTEXT(String);

	return msg(StringClass, "newWithCString", self->value);
}

DEFINE(length) {
	CONTEXT(String);

	Integer length = msg(IntegerClass, "newWithInt", strlen(self->value));

	return length;
}

DEFINE(description) {
	return copy(v, args);
}

DEFINE(equals) {
	CONTEXT(String);
	cstring other = NEXT_ARG(cstring);
	if (strncmp(self->value, other, strlen(self->value)) == 0) {
		return YES;
	}
	
	return NO;
}
