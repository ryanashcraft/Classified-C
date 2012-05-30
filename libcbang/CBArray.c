
#include "CBang.h"

Class ArrayClass = NULL;

static void *newWithObjects(void *v, va_list *args);

static void *initWithObjects(void *v, va_list *args);
static void *dealloc(void *v, va_list *args);
static void *performMethodOnEach(void *v, va_list *args);
static void *get(void *v, va_list *args);
static void *length(void *v, va_list *args);

void array_class_init() {
	ArrayClass = msg(ClassClass, "new", "Array", ObjectClass);

	push_back(ArrayClass->static_methods, mmethod("newWithObjects", &newWithObjects));
	
	push_back(ArrayClass->instance_methods, mmethod("initWithObjects", &initWithObjects));
	push_back(ArrayClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(ArrayClass->instance_methods, mmethod("performMethodOnEach", &performMethodOnEach));
	push_back(ArrayClass->instance_methods, mmethod("get", &get));
	push_back(ArrayClass->instance_methods, mmethod("length", &length));
}

void *newWithObjects(void *v, va_list *args) {
	Array o = cballoc(sizeof(struct _CBArray));
	initWithObjects(o, args);
	((Object)o)->root = ArrayClass;
	return o;
}

void *initWithObjects(void *v, va_list *args) {
	Array o = (Array)v;
	msg_cast(ObjectClass, o, "init");

	o->capacity = 0;
	o->length = 0;

	Object element = NULL;
	va_list duplicate_arg_list;
	va_copy(duplicate_arg_list, *args);
	while ((element = va_arg(duplicate_arg_list, Object)) != NULL) {
		o->capacity++;
	}
	o->capacity++; /* for NULL terminator */

	o->value = calloc(o->capacity, sizeof(Object));
	assert(o->value);
	int i;
	for (i = 0; (element = va_arg(*args, Object)) != NULL; i++) {
		o->value[i] = element;
		msg(element, "retain");
		o->length++;
	}

	return o;
}

void *dealloc(void *v, va_list *args) {
	Array o = (Array)v;

	Object element = NULL;
	int i;
	for (i = 0; (element = o->value[i]) != NULL; i++) {
		msg(element, "release");
	}

	free(o->value);

	return msg_cast(ObjectClass, o, "dealloc");
}

void *performMethodOnEach(void *v, va_list *args) {
	Array o = (Array)v;

	cstring method_name = va_arg(*args, cstring);
	Object element = NULL;
	int i;
	for (i = 0; (element = o->value[i]) != NULL; i++) {
		msg(element, method_name);
	}

	return o;
}

void *get(void *v, va_list *args) {
	Array o = (Array)v;

	int index = va_arg(*args, int);

	Object obj = o->value[index];

	return obj;
}

void *length(void *v, va_list *args) {
	Array o = (Array)v;

	return msg(IntegerClass, "newWithInt", o->length);
}
