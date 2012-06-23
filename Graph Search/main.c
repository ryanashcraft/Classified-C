
#include "../libclassc/classified-c.h"
#include "GraphSearch.h"
#include "Path.h"
#include "Vertex.h"
#include "Pair.h"

int main(int argc, char **argv) {
	cc_init();
	GraphSearchInit();
	// queue_class_init();
	// priority_queue_class_init();
	// adjacency_list_class_init();
	PairInit();
	PathInit();
	// edge_class_init();
	VertexInit();
	// dijkstra_comparator_class_init();
	// prim_comparator_class_init();

	Stack stack = msg(StackClass, "new");
	GraphSearch search = msg(GraphSearchClass, "new", stack);
	msg(stack, "release");
	
	msg(search, "runWithVertex");
	msg(search, "release");
}
