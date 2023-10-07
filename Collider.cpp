#include "Colors.h"
#include "AABB.h"
#include "CollisionShape.h"
#include "Debug.h"
#include "Collider.h"
#include <glm/glm/glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include <array>
#include <string>

namespace WIP_Polygon {
	Collider::Collider() :
		center{},
		u{},
		e{},
		rotation{},
		scale{},
		m_localToWorld{},
		aabb{},
		collider{ nullptr },
		name{ "none" },
		color{ 0.0f, 1.0f, 0.0f, 1.0f },
		enable_render {true},
		is_static {true},
		manifold{}
	{}
	Collider::Collider(glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation) :
		center{ _position },
		rotation{
			glm::normalize(
				 glm::angleAxis(glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) * 
				 glm::angleAxis(glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) * 
				 glm::angleAxis(glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f))
			)
		},
		u{
			glm::normalize(rotation * glm::vec3(1.0f,0.0f,0.0f)), 
			glm::normalize(rotation * glm::vec3(0.0f,1.0f,0.0f)),
			glm::normalize(rotation * glm::vec3(0.0f,0.0f,1.0f)) 
		},
		e{ _scale * 0.5f },
		scale{ _scale },
		m_localToWorld{
			glm::translate(glm::mat4(1.0f), _position) * 
			(
				glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f))
			) *
			glm::scale(glm::mat4(1.0f), _scale) 
		},
		color{ 0.0f, 1.0f, 0.0f, 1.0f },
		is_static{true},
		manifold{}
	{}
	void Collider::UpdateTransform(glm::vec3 _position, glm::quat _rotation, glm::vec3 _scale) {
		center = _position;
		m_localToWorld = glm::translate(glm::mat4(1.0f), _position) * glm::toMat4(_rotation) * glm::scale(glm::mat4(1.0f), _scale);
	}
	glm::vec3 Collider::GetSupport(glm::vec3 direction) {
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

	Collider::~Collider() {}
}
