
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "list.h"

#include "objc.h"

class *objc_null;

obj *_constructor();
void *_desc(obj *obj);

class *_objc_null_init() {
	objc_null = malloc(sizeof(class));
	assert(objc_null);

	objc_null->name = "NULL";
	list *objc_null_vtable = create_list();
	objc_null->v_table = objc_null_vtable;

	objc_null->constructor = &_constructor;

	string method_name = "desc";
	method *objc_null_desc = malloc(sizeof(method));
	assert(objc_null_desc);
	objc_null_desc->name = malloc(sizeof(char) * strlen(method_name));
	assert(objc_null_desc->name);
	strcpy(objc_null_desc->name, method_name);
	objc_null_desc->f_pointer = &_desc;
	objc_null_desc->return_type = objc_null;

	push_back(objc_null_vtable, objc_null_desc);

	return objc_null;
}

obj *_constructor() {
	obj *null;

	null = malloc(sizeof(obj));
	assert(null);

	null->class = objc_null;

	return null;
}

void *_desc(obj *obj) {
	printf("%s", obj->class->name);

	return 0;
}