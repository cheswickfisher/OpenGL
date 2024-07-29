#include "Rigidbody.h"

namespace WIP_Polygon {
	Rigidbody::Rigidbody()
		: GameObject{},
		moveDirection(glm::vec3(0.0f)), velocity{ 0.0f }, acceleration{ 0.0f }, mass{ 0.0f }, 
		torque{0.0f}, angular_velocity{0.0f}, angular_acceleration{0.0f}, inertia_tensor{1.0f},
		collider{ nullptr }, 
		force{0.0f}, 
		pid{}
	{
	}
	Rigidbody::Rigidbody(glm::vec3 _scale, float _mass, WIP_Polygon::Collider* _col)
		: GameObject{ _scale },
		moveDirection(glm::vec3(0.0f)), velocity{ 0.0f }, acceleration{ 0.0f }, mass{ _mass }, 
		torque{0.0f}, angular_velocity{ 0.0f }, angular_acceleration{ 0.0f }, inertia_tensor{ 1.0f },
		collider {_col},
		force{0.0f}, 
		pid{}
	{
	}
	Rigidbody::Rigidbody(glm::vec3 _scale, glm::vec3 _position, float _mass, WIP_Polygon::Collider* _col)
		: GameObject{ _scale, _position },
		moveDirection(glm::vec3(0.0f)), velocity{ 0.0f }, acceleration{ 0.0f }, mass{ _mass }, 
		torque{0.0f}, angular_velocity{ 0.0f }, angular_acceleration{ 0.0f }, inertia_tensor{ 1.0f },
		collider {_col}, 
		force{0.0f},
		pid{}
	{
	}
	Rigidbody::Rigidbody(glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation, float _mass, WIP_Polygon::Collider* _col)
		: GameObject{ _scale, _position, _rotation },
		moveDirection(glm::vec3(0.0f)), velocity{ 0.0f }, acceleration{ 0.0f }, mass{ _mass }, 
		torque{0.0f}, angular_velocity{ 0.0f }, angular_acceleration{ 0.0f }, inertia_tensor{ 1.0f },
		collider {_col}, 
		force{0.0f},
		pid{}
	{
	}
	void Rigidbody::UpdatePosition(glm::vec3 _position) {
		moveDirection = glm::normalize(_position - position);
		velocity = (_position - position) / fixed_dt;
		//std::cout << "velocity [" << velocity.x << ", " << velocity.y << ", " << velocity.z << "]\n";
		position = _position;
	}
	void Rigidbody::AddForce(glm::vec3 _force) {
		force += _force;
	}
	void Rigidbody::AddTorque(glm::vec3 _torque) {
		// _torque is the axis of rotation. its magnitude is the amount of spin.
		torque += _torque;
	}
	void Rigidbody::ApplyForces() {
		acceleration = force / mass;
		//std::cout << "rb_name: " << name << " acceleration: (" << acceleration.x << "," << acceleration.y << "," << acceleration.z << "\n";
		velocity = velocity + acceleration;// +p_v;
		angular_acceleration = torque / mass;
		angular_velocity = angular_velocity + angular_acceleration;
	}
	void Rigidbody::ClearForces() {
		force = glm::vec3(0.0f);
		torque = glm::vec3(0.0f);
	}
	void Rigidbody::ClearTransform() {
		//acceleration = glm::vec3(0.0f);
		//velocity = glm::vec3(0.0f);
		//torque = glm::vec3(0.0f);
		//angular_velocity = glm::vec3(0.0f);
		//pitch_delta = 0.0f;
		//yaw_delta = 0.0f;
		//roll_delta = 0.0f;
	}
	void Rigidbody::UpdateTransform() {
		position = position + velocity;
		//glm::quat delta_rotation = glm::quat(glm::vec3(-pitch_delta, yaw_delta, roll_delta));
		glm::quat delta_rotation = glm::quat(angular_velocity);
		rotation = rotation * delta_rotation;
		m_localToWorld = glm::translate(glm::mat4(1.0f), position) * glm::toMat4(rotation) * glm::scale(glm::mat4(1.0f), scale);
	}
	void Rigidbody::UpdateAllTransforms() {
		position = position + velocity;
		glm::quat delta_rotation = glm::quat(angular_velocity);
		rotation = rotation * delta_rotation;
		m_localToWorld = glm::translate(glm::mat4(1.0f), position) * glm::toMat4(rotation) * glm::scale(glm::mat4(1.0f), scale);
		collider->UpdateTransform(position, rotation, collider->scale);
		UpdateInertiaTensor(); //update the inertia tensor
		collider->aabb->center = position;
		collider->aabb->ConstructFromPointSet(collider);
	}
	void Rigidbody::UpdateInertiaTensor() {
		inertia_tensor = collider->CalculateInertiaTensor();
	}
}