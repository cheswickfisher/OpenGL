#include "Camera.h"

namespace WIP_Polygon {
	Camera::Camera() :
		cameraSpeed{5.0f}, sensitivity{0.001f}, posOffset{3.0f},
		pitch{ 0.0f }, yaw{ 0.0f }, fov{45.0f}, cameraRot {glm::quat(1.0f, 0.0f, 0.0f, 0.0f)	},
		cameraPos{ glm::vec3(0.0f, 0.0f, 3.0f) }, cameraFront{ glm::vec3(0.0f, 0.0f, 1.0f) },
		worldUp{ glm::vec3(0.0f, 1.0f, 0.0f) }, forward{ glm::vec4(0.0f, 0.0f, 1.0f, 0.0f) },
		view{}, projection{}
	{
	}

	void Camera::UpdateRotation() {
		glm::quat qPitch = glm::angleAxis(pitch, glm::vec3(1.0f, 0.0f, 0.0f));
		glm::quat qYaw = glm::angleAxis(yaw, glm::vec3(0.0f, 1.0f, 0.0f));
		cameraRot = glm::normalize(qPitch * qYaw);
		cameraFront = glm::normalize(glm::conjugate(cameraRot) * (forward));
	}

	void Camera::UpdatePosition(glm::vec3 target) {
		cameraPos = target - Front() * posOffset;
	}

	glm::mat4 Camera::ViewMatrix() {
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
		view = rotate * translate;
		return view;
	}

	glm::mat4 Camera::ProjectionMatrix() {		
		projection = glm::perspective(glm::radians(fov), a, 0.1f, 100.0f);
		return projection;
	}

	glm::vec3 Camera::Front() {
		return -cameraFront;
	}
}
