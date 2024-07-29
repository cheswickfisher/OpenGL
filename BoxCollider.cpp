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
	glm::mat3 BoxCollider::CalculateInertiaTensor() {
		//formulas from https://en.wikipedia.org/wiki/Moment_of_inertia#Inertia_tensor
		float ex2 = 4.0f * e.x * e.x;
		float ey2 = 4.0f * e.y * e.y;
		float ez2 = 4.0f * e.z * e.z;
		float mass = aabb->rigidbody->mass;
		float Ixx = 1.0f / 12.0f * mass * (ey2 * ez2);
		float Iyy = 1.0f / 12.0f * mass * (ex2 * ez2);
		float Izz = 1.0f / 12.0f * mass * (ex2 * ey2);
		glm::mat3 i_t = glm::mat3(1.0f);
		i_t[0][0] = Ixx;
		i_t[1][1] = Iyy;
		i_t[2][2] = Izz;
		glm::vec3 position = aabb->rigidbody->position;
		glm::quat rot = aabb->rigidbody->rotation;
		//transform inertia tensor to world space
		glm::mat3 R = glm::toMat3(rot);
		i_t = R * i_t * glm::transpose(R); //rotation
		i_t += mass * (glm::dot(position, position) * glm::mat3(1.0f) - glm::outerProduct(position, position)); //translation
		return i_t;
	}
}