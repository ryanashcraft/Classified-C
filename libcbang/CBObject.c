
#include "CBang.h"
#include "CBObject.h"

Class ObjectClass = NULL;

static void *init(void *v, va_list *args);
static void *initWithPointer(void *v, va_list *args);
static void *super(void *v);

static void *print(void *v, va_list *args);
static void *release(void *v, va_list *args);

void object_class_init() {
	method m;


	// ObjectClass->class = ObjectClass;
	// ObjectClass->name = mstring("ObjectClass");

	// ObjectClass = malloc(sizeof(struct _CBObject));
	// assert(ObjectClass);
	// ObjectClass->class = ObjectClass;

	ObjectClass = message(ClassClass, "init", "ObjectClass", NULL, &super);

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

void *super(void *v) {
	return NULL;
}

void *print(void *v, va_list *args) {
	fprintf(stderr, "Object");
	return NULL;
}

void *release(void *v, va_list *args) {
	Object o = (Object)v;
	free_list(o->methods, &free);
	// free(o);
	return o;
}
