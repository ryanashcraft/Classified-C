
#define CLASS Null
#define SUPER Object

#include "Classified-C.h"

proto(new);

defclass {
	constructor(new);
} end

defcon(new) {
	return self;
} end
