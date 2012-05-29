
#include "../libcbang/CBang.h"

Class MutableStringClass = NULL;

static void *newWithCString(void *v, va_list *args);
static void *newWithCStringAndCapacity(void *v, va_list *args);

static void *initWithCString(void *v, va_list *args);
static void *initWithCStringAndCapacity(void *v, va_list *args);
static void *dealloc(void *v, va_list *args);
static void *concatenateWithCString(void *v, va_list *args);
static void *concatenateWithString(void *v, va_list *args);
static void *appendCharacter(void *v, va_list *args);
static void *vsprint(void *v, va_list *args);

static cstring concatenate(MutableString s, cstring part_two);

void mutable_string_class_init() {
	MutableStringClass = msg(ClassClass, "new", "MutableString", StringClass);

	push_back(MutableStringClass->static_methods, mmethod("newWithCString", &newWithCString));
	push_back(MutableStringClass->static_methods, mmethod("newWithCStringAndCapacity", &newWithCStringAndCapacity));

	push_back(MutableStringClass->instance_methods, mmethod("initWithCString", &initWithCString));
	push_back(MutableStringClass->instance_methods, mmethod("initWithCStringAndCapacity", &initWithCStringAndCapacity));
	push_back(MutableStringClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(MutableStringClass->instance_methods, mmethod("concatenateWithCString", &concatenateWithCString));
	push_back(MutableStringClass->instance_methods, mmethod("concatenateWithString", &concatenateWithString));
	push_back(MutableStringClass->instance_methods, mmethod("appendCharacter", &appendCharacter));
	push_back(MutableStringClass->instance_methods, mmethod("vsprint", &vsprint));
}

void *newWithCString(void *v, va_list *args) {
	MutableString o = cballoc(sizeof(struct _CBMutableString));
	initWithCString(o, args);
	((Object)o)->root = MutableStringClass;

	return o;
}

void *newWithCStringAndCapacity(void *v, va_list *args) {
	MutableString o = cballoc(sizeof(struct _CBMutableString));
	initWithCStringAndCapacity(o, args);
	((Object)o)->root = MutableStringClass;

	return o;
}

void *initWithCString(void *v, va_list *args) {
	MutableString o = (MutableString)v;
	msg_cast(ObjectClass, o, "init");
	msg_cast(StringClass, o, "initWithCString", va_arg(*args, cstring));

	o->capacity = strlen(o->base.value);

	return o;
}

void *initWithCStringAndCapacity(void *v, va_list *args) {
	MutableString o = (MutableString)v;
	msg_cast(ObjectClass, o, "init");
	msg_cast(StringClass, o, "initWithCString", va_arg(*args, cstring));

	o->capacity = va_arg(*args, int);
	int string_length = strlen(o->base.value);
	o->base.value = realloc(o->base.value, o->capacity);
	o->base.value[string_length] = '\0';

	return o;
}

void *dealloc(void *v, va_list *args) {
	MutableString o = (MutableString)v;
	return msg_cast(StringClass, o, "dealloc");
}

void *concatenateWithCString(void *v, va_list *args) {
	MutableString o = (MutableString)v;

	cstring part_two = va_arg(*args, cstring);
	o->base.value = concatenate(o, part_two);

	return o;
}

void *concatenateWithString(void *v, va_list *args) {
	MutableString o = (MutableString)v;

	String stringArgument = (String)va_arg(*args, String);
	cstring part_two = stringArgument->value;
	o->base.value = concatenate(o, part_two);

	return o;
}

cstring concatenate(MutableString o, cstring part_two) {
	int part_one_length = strlen(o->base.value);
	int part_two_length = strlen(part_two);

	if (part_one_length + part_two_length + 1 > o->capacity) {
		o->base.value = realloc(o->base.value, o->capacity * 2 + part_two_length + 1);
		assert(o->base.value);
	}
 	
	strncat(o->base.value, part_two, part_two_length);

	return o->base.value;
}

void *appendCharacter(void *v, va_list *args) {
	MutableString o = (MutableString)v;
	char c = (char)va_arg(*args, int);

	int string_length = strlen(o->base.value);

	if (string_length + 2 >= o->capacity) {
		o->capacity *= 2;
		o->base.value = realloc(o->base.value, o->capacity);
		assert(o->base.value);
	}

	o->base.value[string_length] = c;
	o->base.value[string_length + 1] = '\0';

	return o;
}

void *vsprint(void *v, va_list *args) {
	MutableString o = (MutableString)v;

	cstring dup = mstring(o->base.value);

	va_list *format_args = va_arg(*args, va_list *);
	va_list duplicate_format_args;
	va_copy(duplicate_format_args, *format_args);
	size_t required = vsnprintf(NULL, 0, dup, duplicate_format_args);
	if (required >= o->capacity) {
		o->capacity += required;
		o->base.value = realloc(o->base.value, o->capacity);
		assert(o->base.value);
	}
	vsprintf(o->base.value, dup, *format_args);

	free(dup);

	int string_length = strlen(o->base.value);
	o->base.value[string_length] = '\0';

	return o;
}
