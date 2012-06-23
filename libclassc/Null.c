
#include "Classified-C.h"

#define TYPE Null
#define SUPER ObjectClass

proto(new);

defclass
	static(new);
end

defcon(new)
	return self;
end
