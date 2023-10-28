#ifndef COLLIDER_H
#define COLLIDER_H
#include "Colors.h"
#include "AABB.h"
#include "CollisionShape.h"
#include "Debug.h"
#include "Manifold.h"
#include <glm/glm/glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include <array>
#include <string>

namespace WIP_Polygon {
	class AABB;
	//class Collider;
	class Collider {
	public:
		glm::vec3 center;
		std::array<glm::vec3, 3> u;
		glm::vec3 e;
		glm::quat rotation;
		glm::vec3 scale;
		glm::mat4 m_localToWorld;
		AABB* aabb;
		WIP_Polygon::CollisionShape* collider;
		WIP_Polygon::ContactManifold manifold;
		std::string name;
		glm::vec4 color;
		bool enable_render;
		Collider();
		Collider(glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation, CollisionShape* _collider);
		void UpdateTransform(glm::vec3 _position, glm::quat _rotation, glm::vec3 _scale);
		glm::vec3 GetSupport(glm::vec3 direction);
		virtual ~Collider() = 0;
		virtual void DrawAxes() = 0;

	};
}

#endif