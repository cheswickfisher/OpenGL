#ifndef COLLIDER_H
#define COLLIDER_H
#include "Colors.h"
#include "AABB.h"
#include "CollisionShape.h"
#include "Debug.h"
#include <glm/glm/glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include <array>
#include <string>

namespace WIP_Polygon {
	class Collider {
	public:
		glm::vec3 center;
		std::array<glm::vec3, 3> u;
		glm::vec3 e;
		glm::quat rotation;
		glm::vec3 scale;
		glm::mat4 m_localToWorld;
		AABB aabb;
		WIP_Polygon::CollisionShape* collider;
		std::string name;
		glm::vec4 color;
		bool enable_render;
		Collider();
		Collider(glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation);
		void UpdateTransform(glm::vec3 _position, glm::quat _rotation, glm::vec3 _scale);
		glm::vec3 GetSupport(glm::vec3 direction);
		virtual ~Collider() = 0;
		virtual void DrawAxes() = 0;

	};
	/*class Collider {
	public:
		glm::vec3 center{};
		std::array<glm::vec3, 3> u{};
		glm::vec3 e{};
		glm::quat rotation{};
		glm::vec3 scale{};
		glm::mat4 m_localToWorld{};
		AABB aabb{};
		WIP_Polygon::CollisionShape* collider{};
		std::string name{"none"};
		Collider() {
		};
		Collider(glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation) {
			center = _position;
			glm::quat qPitch = glm::angleAxis(_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			glm::quat qYaw = glm::angleAxis(_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			glm::quat qRoll = glm::angleAxis(_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
			rotation = glm::normalize(qPitch * qYaw * qRoll);
			u = { glm::normalize(rotation * glm::vec3(1.0f,0.0f,0.0f)), glm::normalize(rotation * glm::vec3(0.0f,1.0f,0.0f)), glm::normalize(rotation * glm::vec3(0.0f,0.0f,1.0f)) };
			e = _scale * 0.5f;
			scale = _scale;
			glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 rot_combined = rotX * rotY * rotZ;
			m_localToWorld = glm::translate(glm::mat4(1.0f), center) * rot_combined * glm::scale(glm::mat4(1.0f), scale);
		};

		void UpdateTransform(glm::vec3 _position, glm::quat _rotation, glm::vec3 _scale) {
			center = _position;
			m_localToWorld = glm::translate(glm::mat4(1.0f), _position) * glm::toMat4(_rotation) * glm::scale(glm::mat4(1.0f), _scale);
		}

		glm::vec3 GetSupport(glm::vec3 direction)  {
			float best_projection = std::numeric_limits<float>::lowest();
			glm::vec3 best_vertex = glm::vec3(0.0);
			for (int i = 0; i < collider->vertices.size(); i++) {
				glm::vec3 v = m_localToWorld * glm::vec4(collider->vertices[i].position, 1.0f);
				float projection = glm::dot(v, direction);

				if (projection > best_projection) {
					best_projection = projection;
					best_vertex = v;
				}
			}
			return best_vertex;
		}
		virtual ~Collider() = 0;
		virtual void DrawAxes() = 0;
	};
	Collider::~Collider() {}*/
}

#endif