#include "GameObject.h"

GameObject::GameObject() :
position{},
scale{glm::vec3(1.0f)},
rotation{ glm::quat(1.0f, 0.0f, 0.0f, 0.0f) },
m_localToWorld{1.0f},
pitch{},
yaw{},
roll{},
pitch_delta{},
yaw_delta{},
roll_delta{},
mesh_renderer{nullptr}
{}

GameObject::GameObject(glm::vec3 _scale) :
	position{ glm::vec3(0.0f) },
	scale{ _scale },
	rotation{ glm::quat(1.0f, 0.0f, 0.0f, 0.0f) },
	m_localToWorld{
		glm::translate(glm::mat4(1.0f), position)*
		(
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f))*
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f))*
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f))
		)*
		glm::scale(glm::mat4(1.0f), scale)
	},
	pitch{ 0.0f },
	yaw{0.0f}, 
	roll{ 0.0f },
	pitch_delta{ 0.0f },
	yaw_delta{0.0f}, 
	roll_delta{ 0.0f },
	mesh_renderer{nullptr}
{}

GameObject::GameObject(glm::vec3 _scale, glm::vec3 _position) :
	position{_position}, 
	scale{ _scale },
	rotation{ glm::quat(1.0f, 0.0f, 0.0f, 0.0f) },
	m_localToWorld{
	glm::translate(glm::mat4(1.0f), position) *
	(
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f))
	) *
	glm::scale(glm::mat4(1.0f), scale)
	},
	pitch{ 0.0f },
	yaw{0.0f}, 
	roll{ 0.0f },
	pitch_delta{ 0.0f },
	yaw_delta{ 0.0f },
	roll_delta{0.0f},
	mesh_renderer{ nullptr }
{}

GameObject::GameObject(glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation) :
	position{_position},
	scale{ _scale },
	rotation{
		glm::normalize(glm::angleAxis(glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f))
			* glm::angleAxis(glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f))
			* glm::angleAxis(glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)))
	},
	m_localToWorld{
		glm::translate(glm::mat4(1.0f), position) *
		(
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f))
		) *
		glm::scale(glm::mat4(1.0f), scale)
	},
	pitch{ glm::radians(_rotation.x) },
	yaw{ glm::radians(_rotation.y) },
	roll{ glm::radians(_rotation.z) },
	pitch_delta{ 0.0f },
	yaw_delta{ 0.0f },
	roll_delta{ 0.0f },
	mesh_renderer{ nullptr }
{}

glm::vec3 GameObject::Forward() {
	return rotation * glm::vec3(0.0f, 0.0f, 1.0f);
}

glm::vec3 GameObject::Right() {
	return rotation * glm::vec3(1.0f, 0.0f, 0.0f);
}

glm::vec3 GameObject::Up() {
	return rotation * glm::vec3(0.0f, 1.0f, 0.0f);
}

void GameObject::UpdatePosition() {

}

void GameObject::UpdateRotation() {
	glm::quat delta_rotation = glm::quat(glm::vec3(-pitch_delta, yaw_delta, roll_delta));
	rotation = rotation * delta_rotation;
	pitch_delta = 0.0f;
	yaw_delta = 0.0f;
	roll_delta = 0.0f;
}

void GameObject::UpdateTransform() {
	glm::quat delta_rotation = glm::quat(glm::vec3(-pitch_delta, yaw_delta, roll_delta));
	rotation = rotation * delta_rotation;
	pitch_delta = 0.0f;
	yaw_delta = 0.0f;
	roll_delta = 0.0f;	
	m_localToWorld = glm::translate(glm::mat4(1.0f), position) * glm::toMat4(rotation) * glm::scale(glm::mat4(1.0f), scale);
}





