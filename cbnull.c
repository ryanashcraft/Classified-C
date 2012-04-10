
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "list.h"

#include "cbang.h"

class *this;

var _constructor();
var _desc(var obj);

class *_objc_null_init() {
	string tname = "Null";
	string name = malloc(sizeof(char) * (strlen(tname) + 1));
	assert(name);
	strcpy(name, tname);
	this = cbang_class_init(name, &_constructor);

	/* Description method */
	method *desc = malloc(sizeof(method));
	assert(desc);
	tname = "describe";
	name = malloc(sizeof(char) * (strlen(tname) + 1));
	assert(name);
	strcpy(name, tname);
	desc = cbang_method_init(name, &_desc);
	push_back(this->v_table, desc);

	return this;
}

obj *_constructor() {
	obj *null;

	null = malloc(sizeof(obj));
	assert(null);

	null->class = this;

	return null;
}

var _desc(var v) {
	return v;
}