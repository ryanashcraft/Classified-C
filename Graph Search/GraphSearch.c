
#define CLASS GraphSearch
#define SUPER Object

#include "../libclassc/classified-c.h"
#include "GraphSearch.h"
#include "Path.h"
#include "Vertex.h"
#include "Pair.h"

proto(new);
proto(dealloc);
proto(runWithVertex);
proto(makeEdgeList);

defclass
	static(new);

	instance(dealloc);
	instance(runWithVertex);
	instance(makeEdgeList);
end

defcon(new)
	self->ds = NEXT_ARG(Object);
	msg(self->ds, "retain");
	self->results = msg(LinkedListClass, "new");
	self->edgeList = msg(LinkedListClass, "new");
	self->visited = msg(LinkedListClass, "new");

	return self;
end

def(dealloc)
	msg(self->ds, "release");
	msg(self->results, "release");
	msg(self->edgeList, "release");
	msg(self->visited, "release");

	msgSuper("dealloc");

	return self;
end

def(runWithVertex)
	msg(self->visited, "clear");

	msg(self->ds, msg(PathClass, "newWithVertex", NEXT_ARG(Vertex)));

	while(!msg(self->ds, "isEmpty")) {
		Path currentPath = msg(self->ds, "remove");
		Vertex nextOpenVertex = msg(currentPath, "getLastVertex");

		if (!msg(self->visited, "contains", nextOpenVertex)) {
			msg(self->visited, "add", nextOpenVertex);
			msg(self->results, "add", currentPath);

			Iterator adjacencies = msg(nextOpenVertex, "getAdjacenciesIterator");
			Pair p = NULL;
			while ( (p = msg(adjacencies, "next")) ) {
				Path newPath = msg(PathClass, "newWithPath", currentPath, p);
				msg(self->ds, "add", newPath);
			}
			msg(adjacencies, "release");
		}
	}

	msg(self, "makeEdgeList");

	return self;
end

def(makeEdgeList)
	Iterator adjacencies = msg(IteratorClass, "newWithLinkedList", self->results);
	Path p = NULL;
	while ( (p = msg(adjacencies, "next")) ) {
		msg(self->edgeList, "add", msg(p, "getLastEdge"));
	}

	return self;
end
