
#define CLASS Vertex
#define SUPER Object

#include "../libclassc/Classified-C.h"
#include "main.h"

proto(newWithName);
proto(getAdjacenciesIterator);

defclass
	static(newWithName);

	instance(getAdjacenciesIterator);
end

defcon(newWithName)
	self->adjacencies = msg(LinkedListClass, "new");
	self->name = msg(StringClass, "newWithCString", NEXT_ARG(cstring));
	return self;
end

def(getAdjacenciesIterator)
	return msg(IteratorClass, "newWithLinkedList", self->adjacencies);
end