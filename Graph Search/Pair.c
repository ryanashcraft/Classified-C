
#define CLASS Pair
#define SUPER Object

#include "../libclassc/Classified-C.h"
#include "Pair.h"

proto(new);

defclass
	static(new);
end

def(new)
	return self;
end
