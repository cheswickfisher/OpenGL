#ifndef  MANIFOLD_H
#define MANIFOLD_H

#include "glm\glm\glm.hpp"
#include <vector>
#include <string>

namespace WIP_Polygon {
	struct ContactManifold {
		int contact_point_count;
		std::vector<glm::vec3> contact_points;
		glm::vec3 contact_normal;
		float contact_penetration;
		std::string contact_type;
		ContactManifold();
};
}
#endif

