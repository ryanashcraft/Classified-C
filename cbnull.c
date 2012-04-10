
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "list.h"

#include "cbang.h"

class *this = NULL;

var constructor();
var desc(var obj);

class *cbnull_init() {
	if (this) {
		return this;
	}

	string tname = "CBNull";
	string name = malloc(sizeof(char) * (strlen(tname) + 1));
	assert(name);
	strcpy(name, tname);
	this = cbang_class_init(name, &constructor);

	/* Description method */
	method *method = malloc(sizeof(method));
	assert(method);
	tname = "describe";
	name = malloc(sizeof(char) * (strlen(tname) + 1));
	assert(name);
	strcpy(name, tname);
	method = cbang_method_init(name, &desc);
	push_back(this->v_table, method);

	return this;
}

var constructor() {
	obj *the_obj;
	the_obj = malloc(sizeof(obj));
	assert(the_obj);
	the_obj->class = this;

	return the_obj;
}

var desc(var v) {
	return v;
}