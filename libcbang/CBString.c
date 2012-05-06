
#include "CBang.h"
#include "CBString.h"

Class StringClass = NULL;

static void *newWithString(void *v, va_list *args);

static void *initWithString(void *v, va_list *args);
static void *dealloc(void *v, va_list *args);
static void *concatenate(void *v, va_list *args);
static void *length(void *v, va_list *args);
static void *print(void *v, va_list *args);
static void *toCString(void *v, va_list *args);

void string_class_init() {
	StringClass = msg(ClassClass, "new", "String", ObjectClass);

	push_back(StringClass->static_methods, mmethod("newWithString", &newWithString));

	push_back(StringClass->instance_methods, mmethod("initWithString", &initWithString));
	push_back(StringClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(StringClass->instance_methods, mmethod("concatenate", &concatenate));
	push_back(StringClass->instance_methods, mmethod("length", &length));
	push_back(StringClass->instance_methods, mmethod("print", &print));
	push_back(StringClass->instance_methods, mmethod("toCString", &toCString));
}

void *newWithString(void *v, va_list *args) {
	String o = cballoc(sizeof(struct _CBString));
	initWithString(o, args);
	((Object)o)->root = StringClass;
	return o;
}

void *initWithString(void *v, va_list *args) {
	String o = (String)v;
	object_init(o, StringClass);
	o->value = mstring(va_arg(*args, string));
	return o;
}

void *dealloc(void *v, va_list *args) {
	String o = (String)v;
	free(o->value);
	return msg_super(o, "dealloc");
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
	// String o = (String)v;
	// var length = msg(IntegerClass, "initWithInt", NULL, strlen(o->value));
	// return length;
	return NULL;
}

void *print(void *v, va_list *args) {
	String o = (String)v;
	printf("%s", o->value);
	return o;
}

void *toCString(void *v, va_list *args) {
	String o = (String)v;
	return o->value;
}
