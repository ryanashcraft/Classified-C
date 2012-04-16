
#include "CBang.h"
#include "CBObject.h"

Class ObjectClass = NULL;

static void *init(void *v, va_list *args);

static void *release(void *v, va_list *args);
static void *print(void *v, va_list *args);

void object_class_init() {
	ObjectClass = message(ClassClass, "init", "Object", NULL);

	push_back(ObjectClass->methods, mmethod("init", &init));

	push_back(ObjectClass->instance_methods, mmethod("release", &release));
	push_back(ObjectClass->instance_methods, mmethod("print", &print));
}

void *init(void *v, va_list *args) {
	Object o = calloc(1, sizeof(struct _CBObject));
	assert(o);

	o->class = ObjectClass;
	o->methods = ObjectClass->instance_methods;
	o->parent = NULL;
	o->retaincount = 1;

	return o;
}

void *release(void *v, va_list *args) {
	Object o = (Object)v;
	--o->retaincount;

	if (o->retaincount == 0) {
		free(o);
		return NULL;
	}

	return o;
}

void *print(void *v, va_list *args) {
	fprintf(stderr, "Object");
	return NULL;
}

