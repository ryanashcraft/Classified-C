
#define CLASS Null
#define SUPER Object

#include "Classified-C.h"

proto(new);

defclass
	static(new);
end

defcon(new)
	return self;
end
