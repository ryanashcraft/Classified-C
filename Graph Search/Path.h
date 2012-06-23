
#ifndef PATH_H
#define PATH_H

extern Class PathClass;

typedef struct _Path {
	struct _Object base;
	LinkedList vertices;
	Integer totalWeight;
	Integer lastEdgeWeight;
} *Path;

void PathInit();

#endif