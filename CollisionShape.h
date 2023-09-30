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
		unsigned int id;
		std::vector<Vertex> vertices;
		std::vector<Plane> planes;
		std::vector<HalfEdge> edges;
		CollisionShape();
		virtual ~CollisionShape() = 0;
	};
}
#endif