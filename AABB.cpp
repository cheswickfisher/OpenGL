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
		//BoundingSphere(_rigidbody);
		_rigidbody->collider->aabb = this;
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
	void AABB::ConstructFromPointSet(Collider* a) {
		float x{};
		float y{};
		float z{};

		glm::vec3 max_pt{};
		glm::vec3 min_pt{};

		glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

		AABB::ExtremePointsAlongDirection(right, a->collider->vertices, a, &min_pt, &max_pt);
		x = max_pt.x - min_pt.x;
		AABB::ExtremePointsAlongDirection(up, a->collider->vertices, a, &min_pt, &max_pt);
		y = max_pt.y - min_pt.y;
		AABB::ExtremePointsAlongDirection(forward, a->collider->vertices, a, &min_pt, &max_pt);
		z = max_pt.z - min_pt.z;

		AABB::radius = glm::vec3(glm::abs(x) * 0.5f, glm::abs(y) * 0.5f, glm::abs(z) * 0.5f);
		AABB::center = a->center;
	}
	void AABB::ExtremePointsAlongDirection(glm::vec3 dir, std::vector<Vertex> points, Collider* a, glm::vec3* min_pt, glm::vec3* max_pt) {
		float minproj = std::numeric_limits<float>::max();
		float maxproj = std::numeric_limits<float>::min();
		for (int i = 0; i < points.size(); i++) {
			//only need rotation and scale for transformation
			glm::vec3 pos = glm::vec3(a->m_localToWorld * glm::vec4(points[i].position, 0.0f));
			float proj = glm::dot(pos, dir);
			if (proj < minproj) {
				minproj = proj;
				*min_pt = pos;
			}
			if (proj > maxproj) {
				maxproj = proj;
				*max_pt = pos;
			}
		}
	}

}