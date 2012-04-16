
#include "CBang.h"
#include "CBObject.h"

Class ClassClass = NULL;

static void *init(void *v, va_list *args);

void class_class_init() {
	method m;

	ClassClass = malloc(sizeof(struct _CBClass));
	assert(ClassClass);

	ClassClass->class = ObjectClass;
	ClassClass->name = mstring("ClassClass");
	ClassClass->parent_class = NULL;

	ClassClass->methods = create_list();
	m = mmethod(mstring("init"), &init);
	push_back(ClassClass->methods, m);
}

void *init(void *v, va_list *args) {
	Class c = malloc(sizeof(struct _CBClass));
	assert(c);

	c->class = ClassClass;
	c->methods = create_list();
	c->name = mstring(va_arg(*args, string));
	c->parent_class = va_arg(*args, Class);
	c->super = va_arg(*args, spointer);

	return c;
}
