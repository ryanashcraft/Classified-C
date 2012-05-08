
#include "CBang.h"
#include "CBString.h"

Class StringClass = NULL;

static void *newWithString(void *v, va_list *args);
static void *newWithFormat(void *v, va_list *args);
static void *newWithFormatAndArgList(void *v, va_list *args);

static void *initWithString(void *v, va_list *args);
static void *initWithFormat(void *v, va_list *args);
static void *initWithFormatAndArgList(void *v, va_list *args);
static void *dealloc(void *v, va_list *args);
static void *concatenate(void *v, va_list *args);
static void *length(void *v, va_list *args);
static void *description(void *v, va_list *args);
static void *equals(void *v, va_list *args);

static string format(string format, va_list *format_args);

void string_class_init() {
	StringClass = msg_class(ClassClass, "new", "String", ObjectClass);

	push_back(StringClass->static_methods, mmethod("newWithString", &newWithString));
	push_back(StringClass->static_methods, mmethod("newWithFormat", &newWithFormat));
	push_back(StringClass->static_methods, mmethod("newWithFormatAndArgList", &newWithFormatAndArgList));

	push_back(StringClass->instance_methods, mmethod("initWithString", &initWithString));
	push_back(StringClass->instance_methods, mmethod("initWithFormat", &initWithFormat));
	push_back(StringClass->instance_methods, mmethod("initWithFormatAndArgList", &initWithFormatAndArgList));
	push_back(StringClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(StringClass->instance_methods, mmethod("concatenate", &concatenate));
	push_back(StringClass->instance_methods, mmethod("length", &length));
	push_back(StringClass->instance_methods, mmethod("description", &description));
	push_back(StringClass->instance_methods, mmethod("equals", &equals));
}

void *newWithString(void *v, va_list *args) {
	String o = cballoc(sizeof(struct _CBString));
	initWithString(o, args);
	((Object)o)->root = StringClass;
	return o;
}

void *newWithFormat(void *v, va_list *args) {
	String o = cballoc(sizeof(struct _CBString));
	initWithFormat(o, args);
	((Object)o)->root = StringClass;
	return o;
}

void *newWithFormatAndArgList(void *v, va_list *args) {
	String o = cballoc(sizeof(struct _CBString));
	initWithFormatAndArgList(o, args);
	((Object)o)->root = StringClass;
	return o;
}

void *initWithString(void *v, va_list *args) {
	String o = (String)v;
	msg_cast(ObjectClass, o, "init");
	o->value = mstring(va_arg(*args, string));
	return o;
}

void *initWithFormat(void *v, va_list *args) {
	String o = (String)v;
	msg_cast(ObjectClass, o, "init");
	string formatString = va_arg(*args, string);
	o->value = format(formatString, args);
	return o;
}

void *initWithFormatAndArgList(void *v, va_list *args) {
	String o = (String)v;
	msg_cast(ObjectClass, o, "init");
	string formatString = va_arg(*args, string);
	va_list *formatArgList = va_arg(*args, va_list *);
	o->value = format(formatString, formatArgList);
	return o;
}

string format(string format, va_list *format_args) {
	size_t max_size = 64;
	size_t size = 0;
	string value = calloc(max_size, sizeof(char));
	String arg_string = NULL;
	string arg_string_value = NULL;
	size_t arg_string_length = 0;
	int i;
	for (i = 0; i < strlen(format) + 1; i++) {
		if (i < strlen(format) - 1 && format[i] == '%' && format[i + 1] == '@') {
			arg_string = va_arg(*format_args, String);
			arg_string_value = arg_string->value;
			arg_string_length = strlen(arg_string_value);

			if (size + arg_string_length > max_size) {
				max_size = (max_size * 2) + arg_string_length + 1;
				value = realloc(value, max_size);
			}

			strncat(value, arg_string_value, arg_string_length);
			size += arg_string_length;
			i++;
		} else {
			value[size] = format[i];
			size++;
		}
	}
	value[size] = 0;

	string fully_formatted = calloc(size * 2, sizeof(char));
	vsprintf(fully_formatted, value, *format_args);
	fully_formatted = realloc(fully_formatted, strlen(fully_formatted) + 1);
	assert(fully_formatted);
	free(value);

	return fully_formatted;
}

void *dealloc(void *v, va_list *args) {
	String o = (String)v;
	free(o->value);
	return msg_cast(ObjectClass, o, "dealloc");
}

void *concatenate(void *v, va_list *args) {
	String o = (String)v;

	string part_one = o->value;
	string part_two = va_arg(*args, string);
	int part_one_length = strlen(part_one);
	int part_two_length = strlen(part_two);

	part_one = realloc(part_one, part_one_length + part_two_length + 1);
	assert(part_one);
 	
	strncat(part_one, part_two, part_two_length);

	o->value = part_one;

	return o;
}

void *length(void *v, va_list *args) {
	String o = (String)v;
	Integer length = msg_class(IntegerClass, "newWithInt", strlen(o->value));
	return length;
}

void *description(void *v, va_list *args) {
	String o = (String)v;
	return o;
}

void *equals(void *v, va_list *args) {
	String o = (String)v;
	string other = va_arg(*args, string);
	if (strncmp(o->value, other, strlen(o->value)) == 0) {
		return YES;
	}
	
	return NO;
}
