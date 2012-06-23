
#define CLASS Path
#define SUPER Object

#include "../libclassc/Classified-C.h"
#include "Path.h"

proto(new);

defclass
	static(new);
end

def(new)
	return self;
end
