
#include "../libclassc/classified-c.h"
#include "main.h"

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
	
	Vertex v = msg(VertexClass, "new");
	msg(search, "runWithVertex", v);
	msg(search, "release");
	msg(v, "release");
}
