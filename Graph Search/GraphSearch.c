
#include "../libclassc/classified-c.h"
#include "GraphSearch.h"

IMPLEMENTATION(GraphSearchClass);

PROTOTYPE(new);
PROTOTYPE(dealloc);
PROTOTYPE(runWithVertex);

void graph_search_class_init() {
	GraphSearchClass = msg(ClassClass, "new", "GraphSearch", ObjectClass);

	REGISTER_CLASS_METHOD(GraphSearchClass, "new", new);

	REGISTER_METHOD(GraphSearchClass, "dealloc", dealloc);
	REGISTER_METHOD(GraphSearchClass, "runWithVertex", runWithVertex);
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

	return self;
}
