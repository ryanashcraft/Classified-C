
#include "../libclassc/classified-c.h"
#include "GraphSearch.h"

int main(int argc, char **argv) {
	cc_init();
	graph_search_class_init();
	// queue_class_init();
	// priority_queue_class_init();
	// adjacency_list_class_init();
	// pair_class_init();
	// path_class_init();
	// edge_class_init();
	// vertext_class_init();
	// dijkstra_comparator_class_init();
	// prim_comparator_class_init();

	Stack stack = msg(StackClass, "new");
	GraphSearch search = msg(GraphSearchClass, "new", stack);
	msg(stack, "release");
	
	msg(search, "runWithVertex");
	msg(search, "release");
}
