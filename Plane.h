#ifndef PLANE_H
#define PLANE_H
#include "HalfEdge.h"
#include "Vertex.h"
#include <glm\glm\glm.hpp>
namespace WIP_Polygon {
	struct HalfEdge;
	struct Plane {
		HalfEdge* edge;
		glm::vec3 normal;
		Plane();
	};
}
#endif
