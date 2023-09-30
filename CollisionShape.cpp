#include <vector>
#include "HalfEdge.h"
#include "Plane.h"
#include "Vertex.h"
#include "IDGenerator.h"
#include "CollisionShape.h"
#include <glm/glm/glm.hpp>

namespace WIP_Polygon {
	CollisionShape::CollisionShape() :
		vertices{},
		planes{},
		edges{},
		id{ GenerateID() }
		{}
	CollisionShape::~CollisionShape() {}
};

