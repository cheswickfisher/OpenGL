#include "HalfEdge.h"
#include "Vertex.h"
#include "Plane.h"
#include <iostream>
namespace WIP_Polygon {
	HalfEdge::HalfEdge() :
		index{},
		origin{nullptr},
		incident_face{nullptr},
		//incident_face_b{ nullptr },
		twin{nullptr},
		previous{nullptr},
		next{nullptr}
	{}

	glm::vec3 HalfEdge::Direction() {
		return next->origin->position - origin->position;
	}
}
