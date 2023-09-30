#include "Manifold.h"
namespace WIP_Polygon {
	ContactManifold::ContactManifold() :
		contact_point_count{ 0 },
		contact_points{},
		contact_normal{glm::vec3(0.0f)},
		contact_penetration{ /*std::numeric_limits<float>::max()*/ 0.0f },
		contact_type {}
	{}
}