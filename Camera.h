#ifndef Camera_H
#define Camera_H

#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include <glm/glm/gtc/matrix_access.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Camera {
private:
	glm::vec3 cameraFront;
public:
	float cameraSpeed;
	float sensitivity;
	float posOffset;
	float pitch;
	float yaw;
	glm::quat cameraRot;
	glm::vec3 cameraPos;
	glm::vec3 worldUp;
	glm::vec3 forward;

	Camera() {
		cameraSpeed = 5.0f;
		sensitivity = 0.001f;
		posOffset = 3.0f;
		pitch = 0.0f;
		yaw = 0.0f;
		cameraRot = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
		worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
		forward = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
	}

	void UpdateRotation() {
		glm::quat qPitch = glm::angleAxis(pitch, glm::vec3(1.0f, 0.0f, 0.0f));
		glm::quat qYaw = glm::angleAxis(yaw, glm::vec3(0.0f, 1.0f, 0.0f));
		cameraRot = glm::normalize(qPitch * qYaw);
		cameraFront = glm::normalize(glm::conjugate(cameraRot) * (forward));
	}

	void UpdatePosition(glm::vec3 target) {
		cameraPos = target - Front() * posOffset;
	}

	glm::mat4 ViewMatrix() {
		/*glm::vec3 right = -(glm::cross(cameraFront, worldUp)) / glm::length(glm::cross(cameraFront, worldUp));
		glm::vec3 up = glm::cross(cameraFront, right);
		glm::mat4 rotate = glm::mat4(1.0f);
		rotate[0] = glm::vec4(right,0.0f);
		rotate[1] = glm::vec4(up, 0.0f);
		rotate[2] = glm::vec4(cameraFront, 0.0f);
		rotate = glm::transpose(rotate);*/

		glm::mat4 rotate = glm::mat4_cast(cameraRot);
		glm::mat4 translate = glm::mat4(1.0f);
		translate = glm::translate(translate, -cameraPos);
		glm::mat4 viewMatrix = rotate * translate;
		return viewMatrix;
	}

	glm::vec3 Front() {
		return -cameraFront;
	}
};



#endif