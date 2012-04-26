
#include "CBang.h"
#include "CBObject.h"

Class ObjectClass = NULL;

static void *init(void *v, va_list *args);

static void *release(void *v, va_list *args);
static void *dealloc(void *v, va_list *args);
static void *retain(void *v, va_list *args);
static void *print(void *v, va_list *args);

void object_class_init() {
	ObjectClass = msg(ClassClass, "init", "Object", NULL);

	push_back(ObjectClass->methods, mmethod("init", &init));

	push_back(ObjectClass->instance_methods, mmethod("release", &release));
	push_back(ObjectClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(ObjectClass->instance_methods, mmethod("retain", &retain));
	push_back(ObjectClass->instance_methods, mmethod("print", &print));
}

void *init(void *v, va_list *args) {
	Object o = calloc(1, sizeof(struct _CBObject));
	assert(o);

	Object root = va_arg(*args, Object);
	if (!root) {
		root = (Object)o;
	}

	o->class = ObjectClass;
	o->methods = ObjectClass->instance_methods;
	o->parent = NULL;
	o->root = root;

	o->retaincount = 1;

	return o;
}

void *release(void *v, va_list *args) {
	Object o = (Object)v;
	--o->retaincount;

	if (o->retaincount == 0) {
		return msg(o->root, "dealloc");
	}

	return o->root;
}

void *dealloc(void *v, va_list *args) {
	free(v);
	return NULL;
}

void *retain(void *v, va_list *args) {
	Object o = (Object)v;
	o->retaincount++;
	return o->root;
}

void *print(void *v, va_list *args) {
	fprintf(stderr, "Object");
	return NULL;
}

