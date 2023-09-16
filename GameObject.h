#ifndef  GAMEOBJECT_H
#define GAMEOBJECT_H
#include "BoxCollider.h"
#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>
#include <glm\glm\gtc\quaternion.hpp>
#include <glm\glm\gtx\quaternion.hpp>
#include <iostream>
#include <array>


class GameObject {
public:

	glm::vec3 position;
	glm::vec3 scale;
	glm::quat rotation{};
	float pitch;
	float yaw;
	float roll;
	float pitch_delta{};
	float yaw_delta{};
	float roll_delta{};

	GameObject() {
		position = glm::vec3(0.0f);
		scale = glm::vec3(1.0f, 1.0f, 1.0f);
		rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		pitch = 0.0f;
		yaw = 0.0f;
		roll = 0.0f;
		pitch_delta = 0.0f;
		yaw_delta = 0.0f;
		roll_delta = 0.0f;
	}
	/*GameObject(int _x, int _y, int _z) {
	}*/
	GameObject(glm::vec3 _scale)
		: position(glm::vec3(0.0f)), scale(_scale), rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), pitch(0.0f), yaw(0.0f), roll(0.0f), 
			pitch_delta(0.0f), yaw_delta(0.0f), roll_delta(0.0f)
	{	}

	GameObject(glm::vec3 _scale, glm::vec3 _position)
		: position(_position), scale(_scale), rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), pitch(0.0f), yaw(0.0f), roll(0.0f),
			pitch_delta(0.0f), yaw_delta(0.0f), roll_delta(0.0f)

	{}
	GameObject(glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation)
		: position(_position), scale(_scale), pitch(glm::radians(_rotation.x)), yaw(glm::radians(_rotation.y)), roll(glm::radians(_rotation.z)),
			pitch_delta(0.0f), yaw_delta(0.0f), roll_delta(0.0f)

	{
		glm::quat qPitch = glm::angleAxis(glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::quat qYaw = glm::angleAxis(glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::quat qRoll = glm::angleAxis(glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));		
		rotation = glm::normalize(qPitch * qYaw * qRoll);
	}

	glm::vec3 Forward() {
		return rotation * glm::vec3(0.0f, 0.0f, 1.0f);
	}

	glm::vec3 Right() {
		return rotation * glm::vec3(1.0f, 0.0f, 0.0f);
	}

	glm::vec3 Up() {
		return rotation * glm::vec3(0.0f, 1.0f, 0.0f);
	}

	void UpdatePosition() {

	}

	void UpdateRotation() {
		glm::quat delta_rotation = glm::quat(glm::vec3(-pitch_delta, yaw_delta, roll_delta));
		rotation = rotation * delta_rotation;
		pitch_delta = 0.0f;
		yaw_delta = 0.0f;
		roll_delta = 0.0f;
	}


};
#endif

