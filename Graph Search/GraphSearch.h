
#ifndef GRAPH_SEARCH_H
#define GRAPH_SEARCH_H

extern Class GraphSearchClass;

typedef struct _GraphSearch {
	struct _Object base;
	Object ds;
	LinkedList results;
	LinkedList edgeList;
	LinkedList visited;
} *GraphSearch;

void GraphSearchInit();

#endif
