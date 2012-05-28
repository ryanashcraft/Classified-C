
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
	StringClass = msg(ClassClass, "new", "String", ObjectClass);

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
	size_t value_max_size = 8;
	size_t value_size = 0;
	string value = malloc(sizeof(char) * value_max_size);
	
	size_t buffer_size = 0;
	size_t buffer_max_size = 8;
	string buffer = malloc(sizeof(char) * buffer_max_size);
	
	size_t buffer2_size = 0;
	string buffer2 = NULL;

	string arg_string = NULL;
	size_t arg_string_length = 0;
	
	for (int i = 0; i < strlen(format) + 1; i++) {
		if (format[i] == '%' && format[i + 1] == '@') {
			buffer2_size = vasprintf(&buffer2, buffer, *format_args);

			value = strncat(value, buffer2, buffer2_size);
			value_size += buffer2_size;

			// memset(buffer2, 0, buffer2_size);
			// buffer2_size = 0;
			free(buffer2);

			String arg_object = va_arg(*format_args, String);
			arg_string = (arg_object)->value;
			arg_string_length = strlen(arg_string);

			if (value_size + arg_string_length > value_max_size) {
				value_max_size = (value_max_size * 2) + arg_string_length;
				value = realloc(value, value_max_size + 1);
			}

			value = strncat(value, arg_string, arg_string_length);
			value_size += arg_string_length;

			memset(buffer, 0, buffer_size);
			buffer_size = 0;

			i += 1;
		} else {
			if (buffer_size + 1 > buffer_max_size) {
				buffer_max_size = (buffer_max_size * 2);
				buffer = realloc(buffer, buffer_max_size);
			}

			buffer[buffer_size] = format[i];
			buffer_size++;

			if (i == strlen(format)) {
				buffer2_size = vasprintf(&buffer2, buffer, *format_args);

				if (value_size + buffer2_size > value_max_size) {
					value_max_size = (value_max_size * 2) + buffer2_size;
					value = realloc(value, value_max_size + 1);
				}

				value = strncat(value, buffer2, buffer2_size);
				value_size += buffer2_size;

				// memset(buffer2, 0, buffer2_size);
				// buffer2_size = 0;
				free(buffer2);
			}
		}
	}
	value[value_size] = 0;
	value = realloc(value, strlen(value) + 1);
	free(buffer);

	return value;
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
	Integer length = msg(IntegerClass, "newWithInt", strlen(o->value));
	return length;
}

void *description(void *v, va_list *args) {
	String o = (String)v;
	return msg(StringClass, "newWithString", o->value);
}

void *equals(void *v, va_list *args) {
	String o = (String)v;
	string other = va_arg(*args, string);
	if (strncmp(o->value, other, strlen(o->value)) == 0) {
		return YES;
	}
	
	return NO;
}
