#ifndef VERTEX_H
#define VERTEX_H
#include "glm\glm\glm.hpp"
#include "HalfEdge.h"
namespace WIP_Polygon {
	struct HalfEdge;
	struct Vertex {
		glm::vec3 position	;
		HalfEdge* edge;
		Vertex();
		Vertex(glm::vec3 _position, HalfEdge* _edge);
	};
}
#endif
