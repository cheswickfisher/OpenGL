#ifndef NODE_H
#define NODE_H
#include "glm\glm\glm.hpp"
#include <vector>
#include "AABB.h"
namespace WIP_Polygon {
	struct Node {
		glm::vec3 center;
		float halfWidth;
		std::vector<Node*>pChild;
		AABB* pObjList;
		int level;//for debugging
		Node();
	};
}
#endif
