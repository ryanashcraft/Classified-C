
#include "cbang.h"

static class *this = NULL;

static var constructor();

class *cbnull_init() {
	if (this) {
		return this;
	}

	this = mclass(mstring("CBNull"), &constructor);

	return this;
}

var constructor(va_list args) {
	return mvar(this);
}