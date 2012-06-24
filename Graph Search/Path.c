
#define CLASS Path
#define SUPER Object

#include "../libclassc/Classified-C.h"
#include "main.h"

proto(newWithVertex);
proto(getLastVertex);

defclass
	static(newWithVertex);

	instance(getLastVertex);
end

defcon(newWithVertex)
	self->vertices = msg(LinkedListClass, "new");
	Vertex ver = NEXT_ARG(Vertex);
	msg(self->vertices, "pushBack", ver);
	self->totalWeight = msg(IntegerClass, "newWithInt", 0);
	self->lastEdgeWeight = msg(IntegerClass, "newWithInt", 0);

	return self;
end

def(getLastVertex)
	return msg(self->vertices, "getBack");
end

def(getLastEdge)
	Integer size = msg(self->vertices, "size");
	if (msg(size, "greaterThan", 1)) {
		return msg(EdgeClass, "new", msg(self->vertices, "get", msg(msg(self->vertices, "size"), "subtract", 2)));
	}

	return NULL;
end

def(getPathway)
	return self->vertices;
end

def(description)
	MutableString buffer = msg(MutableStringClass, "new");
	msg(buffer, "append", "Path: ");

	return buffer;
end
