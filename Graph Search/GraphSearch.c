
#include "../libclassc/classified-c.h"
#include "GraphSearch.h"

IMPLEMENTATION(GraphSearchClass);

PROTOTYPE(new);
PROTOTYPE(dealloc);
PROTOTYPE(runWithVertex);
PROTOTYPE(makeEdgeList);

void graph_search_class_init() {
	GraphSearchClass = msg(ClassClass, "new", "GraphSearch", ObjectClass);

	REGISTER_CLASS_METHOD(GraphSearchClass, "new", new);

	REGISTER_METHOD(GraphSearchClass, "dealloc", dealloc);
	REGISTER_METHOD(GraphSearchClass, "runWithVertex", runWithVertex);
	REGISTER_METHOD(GraphSearchClass, "makeEdgeList", makeEdgeList);
}

DEFINE(new) {
	NEW(GraphSearchClass, struct _GraphSearch);

	self->ds = NEXT_ARG(Object);
	msg(self->ds, "retain");
	self->results = msg(LinkedListClass, "new");
	self->edgeList = msg(LinkedListClass, "new");
	self->visited = msg(LinkedListClass, "new");

	return self;
}

DEFINE(dealloc) {
	CONTEXT(GraphSearch);

	msg(self->ds, "release");
	msg(self->results, "release");
	msg(self->edgeList, "release");
	msg(self->visited, "release");

	msg_cast(ObjectClass, self, "dealloc");

	return self;
}

DEFINE(runWithVertex) {
	CONTEXT(GraphSearch);

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
			while ( (p = msg(iterator, "next")) ) {
				Path newPath = msg(PathClass, "newWithPath", currentPath, p);
				msg(self->ds, "add", newPath);
			}
			msg(self->paths, "release");
		}
	}

	msg(self, "makeEdgeList");

	return self;
}

DEFINE(makeEdgeList) {
	CONTEXT(GraphSearch);

	Iterator adjacencies = msg(IteratorClass, "newWithLinkedList", self->results);
	Path p = NULL;
	while ( (p = msg(iterator, "next")) ) {
		msg(self->edgeList, "add", msg(p, "getLastEdge"));
	}

	return self;
}
