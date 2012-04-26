
#include "CBang.h"
#include "CBString.h"

Class StringClass = NULL;

typedef struct _CBString {
	OBJECT_BASE
	
	string value;
} *String;

static void *initWithString(void *v, va_list *args);

static void *dealloc(void *v, va_list *args);
static void *concatenate(void *v, va_list *args);
static void *length(void *v, va_list *args);
static void *print(void *v, va_list *args);
static void *toCString(void *v, va_list *args);

void string_class_init() {
	StringClass = message(ClassClass, "init", "String", ObjectClass);

	push_back(StringClass->methods, mmethod("initWithString", &initWithString));

	push_back(StringClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(StringClass->instance_methods, mmethod("concatenate", &concatenate));
	push_back(StringClass->instance_methods, mmethod("length", &length));
	push_back(StringClass->instance_methods, mmethod("print", &print));
	push_back(StringClass->instance_methods, mmethod("toCString", &toCString));
}

void *initWithString(void *v, va_list *args) {
	String o;

	o = calloc(1, sizeof(struct _CBString));
	assert(o);
	
	Object root = va_arg(*args, Object);
	if (!root) {
		root = (Object)o;
	}

	o->class = StringClass;
	o->methods = StringClass->instance_methods;
	o->parent = message(ObjectClass, "init", root);
	o->root = root;

	o->value = mstring(va_arg(*args, string));

	return o;
}

void *dealloc(void *v, va_list *args) {
	String o = (String)v;
	message(o->parent, "dealloc");
	free(o->value);
	free(o);
	return NULL;
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

	return NULL;
}

void *length(void *v, va_list *args) {
	String o = (String)v;
	var length = message(IntegerClass, "initWithInt", NULL, strlen(o->value));
	return length;
}

void *print(void *v, va_list *args) {
	String o = (String)v;
	printf("%s", o->value);
	return NULL;
}

void *toCString(void *v, va_list *args) {
	String o = (String)v;
	return o->value;
}