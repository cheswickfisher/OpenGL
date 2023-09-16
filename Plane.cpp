#include "Plane.H"
#include "glm\glm\glm.hpp"

namespace WIP_Polygon {
	Plane::Plane() :
		normal{ glm::vec3{} },
		edge{nullptr}
	{}
}