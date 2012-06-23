
#define CLASS Path
#define SUPER Object

#include "../libclassc/Classified-C.h"
#include "main.h"

proto(newWithVertex);

defclass
	static(newWithVertex);
end

defcon(newWithVertex)
	self->vertices = msg(LinkedListClass, "new");
	Vertex ver = NEXT_ARG(Vertex);
	msg(self->vertices, "pushBack", ver);
	self->totalWeight = msg(IntegerClass, "newWithInt", 0);
	self->lastEdgeWeight = msg(IntegerClass, "newWithInt", 0);

	return self;
end
