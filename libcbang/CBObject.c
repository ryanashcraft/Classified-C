
#include "CBang.h"
#include "CBObject.h"

Class ObjectClass = NULL;

static void *init(void *v, va_list *args);
static void *initWithPointer(void *v, va_list *args);

static void *release(void *v, va_list *args);
static void *print(void *v, va_list *args);

void object_class_init() {
	method m;

	ObjectClass = message(ClassClass, "init", "ObjectClass", NULL);

	ObjectClass->methods = create_list();
	m = mmethod("initWithPointer", &initWithPointer);
	push_back(ObjectClass->methods, m);
	m = mmethod("init", &init);
	push_back(ObjectClass->methods, m);

	ObjectClass->parent_class = NULL;
}

void *init(void *v, va_list *args) {
	method m;
	Object o = malloc(sizeof(struct _CBObject));
	assert(o);

	o->class = ObjectClass;
	
	o->methods = create_list();
	m = mmethod("release", &release);
	push_back(o->methods, m);
	m = mmethod("print", &print);
	push_back(o->methods, m);

	o->parent = NULL;

	return o;
}

void *initWithPointer(void *v, va_list *args) {
	method m;
	Object o = va_arg(*args, Object);

	o->class = ObjectClass;

	o->methods = create_list();
	m = mmethod("release", &release);
	push_back(o->methods, m);
	m = mmethod("print", &print);
	push_back(o->methods, m);

	return o;
}

void *release(void *v, va_list *args) {
	Object o = (Object)v;
	free_list(o->methods, &free);
	free(o);
	return o;
}

void *print(void *v, va_list *args) {
	fprintf(stderr, "Object");
	return NULL;
}

