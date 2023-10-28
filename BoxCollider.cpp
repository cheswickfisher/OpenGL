#include "BoxCollider.h"

namespace WIP_Polygon {
	BoxCollider::BoxCollider() :
		Collider{ glm::vec3(1.0f), glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 0.0f), &cube },
		cube{ WIP_Polygon::Cube() }
	{
		name = "box";
	}
	BoxCollider::BoxCollider(glm::vec3 _scale)
		:
		Collider{ _scale, glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 0.0f), &cube },
		cube{ WIP_Polygon::Cube() }
	{
		name = "box";
	}
	BoxCollider::BoxCollider(glm::vec3 _scale, glm::vec3 _position)
		:
		Collider{ _scale, _position,glm::vec3(0.0f, 0.0f, 0.0f), &cube },
		cube{ WIP_Polygon::Cube() }
	{
		name = "box";
	}
	BoxCollider::BoxCollider(glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation)
		:
		Collider{ _scale, _position, _rotation, &cube },
		cube{ WIP_Polygon::Cube() }
	{
		name = "box";
	}
	void BoxCollider::DrawAxes() {
		glm::vec3 f = rotation * glm::vec3(0.0f, 0.0f, 1.0f) * scale.z * 0.5f;
		glm::vec3 r = rotation * glm::vec3(1.0f, 0.0f, 0.0f) * scale.x * 0.5f;
		glm::vec3 u = rotation * glm::vec3(0.0f, 1.0f, 0.0f) * scale.y * 0.5f;

		Debug::DrawDebugLine(center + f, center + f + f * 0.5f, Colors::Cyan, 1.0f);
		Debug::DrawDebugLine(center + r, center + r + r * 0.5f, Colors::Strawberry, 1.0f);
		Debug::DrawDebugLine(center + u, center + u + u * 0.5f, Colors::Green, 1.0f);
	}
}