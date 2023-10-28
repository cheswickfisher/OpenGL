#include "AABB.h"

namespace WIP_Polygon {
	AABB::AABB() :
		pNextObject{ nullptr }, pCurrentNode{ nullptr }, center{ glm::vec3(0.0f) }, radius{ glm::vec3(1.0f) },
		bucket{ 0 }, level{ 0 }, rigidbody{ nullptr }
	{}
	AABB::AABB(glm::vec3 _radius, glm::vec3 _center) :
		pNextObject{ nullptr }, pCurrentNode{ nullptr }, center{ _center }, radius{ _radius },
		bucket{ 0 }, level{ 0 }, rigidbody{ nullptr }
	{}
	AABB::AABB(Rigidbody* _rigidbody) :
		pNextObject{ nullptr }, pCurrentNode{ nullptr }, rigidbody{ _rigidbody }
	{
		BoundingSphere(_rigidbody);
	}
	/*AABB::AABB() :
		pNextObject{ nullptr }, center{ glm::vec3(0.0f) }, radius{ glm::vec3(1.0f) },
		bucket{0}, level{0}, collider{nullptr}
	{}
	AABB::AABB(glm::vec3 _radius, glm::vec3 _center) :
		pNextObject{ nullptr }, center{ _center }, radius{ radius },
		bucket{0}, level{0}, collider{nullptr}
	{}
	AABB::AABB(Collider* _collider) :
		collider{ _collider }
	{
		BoundingSphere(_collider);
	}*/
	void AABB::BoundingSphere(Rigidbody* _rigidbody) {
		float max_distance = -std::numeric_limits<float>::infinity();
		glm::mat4 rs = /*glm::toMat4(_rigidbody->collider->rotation) * */glm::scale(glm::mat4(1.0f), _rigidbody->collider->scale);
		for (int i = 0; i < _rigidbody->collider->collider->vertices.size(); i++) {
			glm::vec3 v = glm::vec3(rs * glm::vec4(_rigidbody->collider->collider->vertices[i].position, 0.0f));
			float sqrd = glm::dot(v, v);
			if (sqrd > max_distance) {
				max_distance = sqrd;
			}
		}
		center = _rigidbody->collider->center;
		radius = glm::vec3(glm::sqrt(max_distance), 0.0f, 0.0f);
	}
}