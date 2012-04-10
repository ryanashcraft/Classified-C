
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "list.h"

#include "cbang.h"

class *objc_null;

var _constructor();
var _desc(var obj);

class *_objc_null_init() {
	objc_null = malloc(sizeof(class));
	assert(objc_null);

	string tname = "Null";
	objc_null->name = malloc(sizeof(char) * (strlen(tname) + 1));
	assert(objc_null->name);
	strcpy(objc_null->name, tname);
	list *objc_null_vtable = create_list();
	objc_null->v_table = objc_null_vtable;

	objc_null->constructor = &_constructor;

	method *objc_null_desc = malloc(sizeof(method));
	assert(objc_null_desc);

	string tmethodname = "describe";
	objc_null_desc->name = malloc(sizeof(char) * (strlen(tmethodname) + 1));
	assert(objc_null_desc->name);
	strcpy(objc_null_desc->name, tmethodname);

	objc_null_desc->f_pointer = &_desc;

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

var _desc(var v) {
	return v;
}