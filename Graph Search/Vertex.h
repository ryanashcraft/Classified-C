
#ifndef VERTEX_H
#define VERTEX_H

extern Class VertexClass;

typedef struct _Vertex {
	struct _Object base;
	LinkedList adjacencies;
	String name;
} *Vertex;

void VertexInit();

#endif