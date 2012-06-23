
#include "Classified-C.h"

#define TYPE Null
#define SUPER ObjectClass

proto(new)

defclass
	registerStatic("new", new);
end

defcon(new)
	return self;
end
