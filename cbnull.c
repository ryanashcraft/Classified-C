
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

	this = cbang_class_init(mstring("CBNull"), &constructor);

	/* Description method */
	method *method = malloc(sizeof(method));
	assert(method);
	method = cbang_method_init(mstring("describe"), &desc);
	push_back(this->methods, method);

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