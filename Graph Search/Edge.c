
#define CLASS Edge
#define SUPER Object

#include "../libclassc/Classified-C.h"
#include "main.h"

proto(new);

defclass
	static(new);
end

defcon(new)
	return self;
end
