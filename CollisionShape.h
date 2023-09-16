#ifndef COLLISIONSHAPE_H
#define COLLISIONSHAPE_H

#include <vector>
#include "HalfEdge.h"
#include "Plane.h"
#include "Vertex.h"
#include "IDGenerator.h"
#include <glm/glm/glm.hpp>

namespace WIP_Polygon {
	struct CollisionShape {
		int id{};
		std::vector<Vertex> vertices{};
		std::vector<Plane> planes{};
		std::vector<HalfEdge> edges{};
		CollisionShape(){
			id = GenerateID();
		}
		virtual ~CollisionShape() = 0;
	};
	CollisionShape::~CollisionShape() {}
}
#endif