#include "Manifold.h"
namespace WIP_Polygon {
	ContactManifold::ContactManifold() :
		contact_point_count{ 0 },
		contact_points{},
		contact_normal{},
		contact_penetration{ /*std::numeric_limits<float>::max()*/ 0.0f },
		contact_type {}
	{}
}