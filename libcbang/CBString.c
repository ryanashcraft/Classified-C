
#include "CBang.h"
#include "CBString.h"

Class StringClass = NULL;

static void *initWithString(void *v, va_list *args);

static void *release(void *v, va_list *args);
static void *concatenate(void *v, va_list *args);
static void *length(void *v, va_list *args);
static void *print(void *v, va_list *args);

void string_class_init() {
	method m;

	StringClass = message(ClassClass, "init", "StringClass", ObjectClass);

	m = mmethod("initWithString", &initWithString);
	push_back(StringClass->methods, m);

	m = mmethod("release", &release);
	push_back(StringClass->instance_methods, m);
	m = mmethod("concatenate", &concatenate);
	push_back(StringClass->instance_methods, m);
	m = mmethod("length", &length);
	push_back(StringClass->instance_methods, m);
	m = mmethod("print", &print);
	push_back(StringClass->instance_methods, m);
}

void *initWithString(void *v, va_list *args) {
	String o;

	o = calloc(1, sizeof(struct _CBString));
	assert(o);
	
	o->class = StringClass;
	o->methods = StringClass->instance_methods;
	o->parent = message(ObjectClass, "init");

	o->value = mstring(va_arg(*args, string));

	return o;
}

void *release(void *v, va_list *args) {
	String o = (String)v;
	free(o->value);
	message(o->parent, "release");
	free(o);
	return o;
}

void *concatenate(void *v, va_list *args) {
	String o = (String)v;

	string part_one = o->value;
	string part_two = mstring(va_arg(*args, string));
	int part_one_length = strlen(part_one);
	int part_two_length = strlen(part_two);

	part_one = realloc(part_one, part_one_length + part_two_length + 1);
	assert(part_one);
 	
	strncat(part_one, part_two, part_two_length);

	o->value = part_one;

	return NULL;
}

void *length(void *v, va_list *args) {
	String o = (String)v;
	Integer length = message(IntegerClass, "initWithInt", strlen(o->value));
	return length;
}

void *print(void *v, va_list *args) {
	String o = (String)v;
	printf("%s", o->value);
	return NULL;
}
