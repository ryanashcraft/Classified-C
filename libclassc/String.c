
#include "Classified-C.h"

#define START_FORMAT_BUFFER_SIZE 32

Class StringClass = NULL;

static void *newWithCString(void *v, va_list *args);
static void *newWithFormatCString(void *v, va_list *args);
static void *newWithFormatCStringAndArgList(void *v, va_list *args);

static void *initWithCString(void *v, va_list *args);
static void *initWithFormatCString(void *v, va_list *args);
static void *initWithFormatCStringAndArgList(void *v, va_list *args);
static void *dealloc(void *v, va_list *args);
static void *copy(void *v, va_list *args);
static void *length(void *v, va_list *args);
static void *description(void *v, va_list *args);
static void *equals(void *v, va_list *args);

static cstring format(cstring format, va_list *format_args);

void string_class_init() {
	StringClass = msg(ClassClass, "new", "String", ObjectClass);

	push_back(StringClass->static_methods, mmethod("newWithCString", &newWithCString));
	push_back(StringClass->static_methods, mmethod("newWithFormatCString", &newWithFormatCString));
	push_back(StringClass->static_methods, mmethod("newWithFormatCStringAndArgList", &newWithFormatCStringAndArgList));

	push_back(StringClass->instance_methods, mmethod("initWithCString", &initWithCString));
	push_back(StringClass->instance_methods, mmethod("initWithFormatCString", &initWithFormatCString));
	push_back(StringClass->instance_methods, mmethod("initWithFormatCStringAndArgList", &initWithFormatCStringAndArgList));
	push_back(StringClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(StringClass->instance_methods, mmethod("copy", &copy));
	push_back(StringClass->instance_methods, mmethod("length", &length));
	push_back(StringClass->instance_methods, mmethod("description", &description));
	push_back(StringClass->instance_methods, mmethod("equals", &equals));
}

void *newWithCString(void *v, va_list *args) {
	String o = cc_alloc(sizeof(struct _String));
	initWithCString(o, args);
	((Object)o)->root = StringClass;
	return o;
}

void *newWithFormatCString(void *v, va_list *args) {
	String o = cc_alloc(sizeof(struct _String));
	initWithFormatCString(o, args);
	((Object)o)->root = StringClass;
	return o;
}

void *newWithFormatCStringAndArgList(void *v, va_list *args) {
	String o = cc_alloc(sizeof(struct _String));
	initWithFormatCStringAndArgList(o, args);
	((Object)o)->root = StringClass;
	return o;
}

void *initWithCString(void *v, va_list *args) {
	String o = (String)v;
	msg_cast(ObjectClass, o, "init");
	cstring string_arg = va_arg(*args, cstring);
	o->value = mstring(string_arg);
	return o;
}

void *initWithFormatCString(void *v, va_list *args) {
	String o = (String)v;
	msg_cast(ObjectClass, o, "init");
	cstring formatString = va_arg(*args, cstring);
	o->value = format(formatString, args);
	return o;
}

void *initWithFormatCStringAndArgList(void *v, va_list *args) {
	String o = (String)v;
	msg_cast(ObjectClass, o, "init");
	cstring formatString = va_arg(*args, cstring);
	va_list *formatArgList = va_arg(*args, va_list *);
	o->value = format(formatString, formatArgList);
	return o;
}

static cstring format(cstring format, va_list *format_args) {
	int format_length = strlen(format);
	MutableString buffer = msg(MutableStringClass, "newWithCStringAndCapacity", "", START_FORMAT_BUFFER_SIZE);

	boolean needsFinalVSprint = NO;
	for (int i = 0; i < format_length; i++) {
		if (i <= format_length && (format[i] == '%' && format[i + 1] == '@')) {
			msg(buffer, "vsprint", format_args);
			String stringArgument = (String)va_arg(*format_args, String);
			msg(buffer, "concatenateWithCString", stringArgument->value);
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

void *dealloc(void *v, va_list *args) {
	String o = (String)v;
	free(o->value);
	return msg_cast(ObjectClass, o, "dealloc");
}

void *copy(void *v, va_list *args) {
	String o = (String)v;
	return msg(StringClass, "newWithCString", o->value);
}

void *length(void *v, va_list *args) {
	String o = (String)v;
	Integer length = msg(IntegerClass, "newWithInt", strlen(o->value));
	return length;
}

void *description(void *v, va_list *args) {
	return copy(v, args);
}

void *equals(void *v, va_list *args) {
	String o = (String)v;
	cstring other = va_arg(*args, cstring);
	if (strncmp(o->value, other, strlen(o->value)) == 0) {
		return YES;
	}
	
	return NO;
}
