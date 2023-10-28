#ifndef AABB_H
#define AABB_H

#include <array>
#include <glm/glm/glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include "Rigidbody.h"
#include "Collider.h"
namespace WIP_Polygon {
	class Rigidbody;
	class Collider;
	class Node;
	class AABB {
	public:
		AABB* pNextObject;
		Node* pCurrentNode;//for debugging so i can visualize node object is in
		glm::vec3 center;
		glm::vec3 test_center;
		glm::vec3 radius;//use x component as radius for bounding sphere
		int bucket;
		int level;
		Rigidbody* rigidbody;
		AABB();
		AABB(glm::vec3 _radius, glm::vec3 _center);
		AABB(Rigidbody* _rigidbody);
		void BoundingSphere(Rigidbody* _rigidbody);
	};
}
#endif
