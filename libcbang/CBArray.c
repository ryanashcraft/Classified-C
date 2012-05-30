
#include "CBang.h"

Class ArrayClass = NULL;

static void *newWithObjects(void *v, va_list *args);

static void *initWithObjects(void *v, va_list *args);
static void *dealloc(void *v, va_list *args);

void array_class_init() {
	ArrayClass = msg(ClassClass, "new", "Array", ObjectClass);

	push_back(ArrayClass->static_methods, mmethod("newWithObjects", &newWithObjects));
	
	push_back(ArrayClass->instance_methods, mmethod("initWithObjects", &initWithObjects));
	push_back(ArrayClass->instance_methods, mmethod("dealloc", &dealloc));
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

	Object element = NULL;
	while((element = va_arg(*args, Object))) {
		
	}

	return o;
}

void *dealloc(void *v, va_list *args) {
	Array o = (Array)v;
	return msg_cast(ObjectClass, o, "dealloc");
}
