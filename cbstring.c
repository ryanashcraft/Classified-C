
#include "cbang.h"

static class *this = NULL;

static var constructor();
static var desc(var obj);

class *cbstring_init() {
	if (this) {
		return this;
	}

	this = mclass(mstring("CBString"), &constructor);

	method *method = mmethod(mstring("describe"), &desc);
	push_back(this->methods, method);

	return this;
}

var constructor() {
	return mvar(this);
}

var desc(var v) {
	return v;
}