#ifndef AABB_H
#define AABB_H

#include <array>
#include <vector>
#include <glm/glm/glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include "Rigidbody.h"
#include "Collider.h"
#include "Vertex.h"
namespace WIP_Polygon {
	class Rigidbody;
	class Collider;
	class Node;
	class AABB {
	public:
		std::string name;//for debugging
		AABB* pNextObject;
		Node* pCurrentNode;//for debugging so i can visualize node object is in
		glm::vec3 center;
		glm::vec3 radius;//half-width extents. use x component as radius for bounding sphere
		int bucket;
		int level;
		Rigidbody* rigidbody;
		AABB();
		AABB(glm::vec3 _radius, glm::vec3 _center);
		AABB(glm::vec3 _radius, glm::vec3 _center, Rigidbody* _rigidbody);
		AABB(Rigidbody* _rigidbody);
		void BoundingSphere(Rigidbody* _rigidbody);
		void ConstructFromPointSet(Collider* a);
		void ExtremePointsAlongDirection(glm::vec3 dir, std::vector<Vertex> points, Collider* a, glm::vec3* min_pt, glm::vec3* max_pt);
		glm::vec3 MinCorner();
	};
}
#endif
