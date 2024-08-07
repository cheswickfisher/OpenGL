#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "GameObject.h"
#include "Collider.h"
#include "PID.h"
#include <glm\glm\glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>

namespace WIP_Polygon {
	class Collider;
	class Rigidbody : public GameObject {
	public:
		WIP_Polygon::Collider* collider;
		glm::vec3 moveDirection; //not using this for anything important
		glm::vec3 velocity;
		glm::vec3 acceleration;
		glm::vec3 angular_acceleration;
		glm::vec3 angular_velocity;
		glm::mat3 inertia_tensor;
		float mass;
		glm::vec3 force;
		glm::vec3 torque;
		WIP_Polygon::PID pid;
		Rigidbody();
		Rigidbody(glm::vec3 _scale, float _mass, WIP_Polygon::Collider* _col);
		Rigidbody(glm::vec3 _scale, glm::vec3 _position, float _mass, WIP_Polygon::Collider* _col);
		Rigidbody(glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation, float _mass, WIP_Polygon::Collider* _col);
		void UpdatePosition(glm::vec3 _position);
		void AddForce(glm::vec3 _force);
		void AddTorque(glm::vec3 _torque);
		void ApplyForces();
		void ClearForces();
		virtual void UpdateTransform();
		void UpdateAllTransforms();
		void ClearTransform();
		void UpdateInertiaTensor();
	};
}
#endif