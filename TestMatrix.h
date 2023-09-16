#ifndef TESTMATRIX_H
#define TESTMATRIX_H
/*#include <glm/glm/glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>*/
/*class TestMatrix {
public:	
	glm::vec3 position{};
	glm::vec3 local_position{};
	glm::vec3 direction{};
	glm::vec3 scale{};
	glm::quat rotation{};
	glm::mat4 m_translation{};
	glm::mat4 m_rotation{};
	glm::mat4 m_scale{};
	glm::mat4 m_localToWorld{};
	float pitch{};
	float yaw{};
	float roll{};
	
	TestMatrix(glm::vec3 _position, glm::vec3 _local_position, glm::vec3 _scale, glm::vec3 _rotation) {
		position = _position;
		local_position = _local_position;
		scale = _scale;
		pitch = glm::radians(_rotation.x);
		yaw = glm::radians(_rotation.y);
		roll = glm::radians(_rotation.z);
		glm::quat qPitch = glm::angleAxis(pitch, glm::vec3(1.0f, 0.0f, 0.0f));
		glm::quat qYaw = glm::angleAxis(yaw, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::quat qRoll = glm::angleAxis(roll, glm::vec3(0.0f, 0.0f, 1.0f));
		rotation = glm::normalize(qPitch * qYaw * qRoll);
		/*glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), pitch, glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), yaw, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), roll, glm::vec3(0.0f, 0.0f, 1.0f));
		m_rotation = rotX * rotY * rotZ;
		m_rotation = glm::mat4_cast(rotation);
		m_translation = glm::translate(glm::mat4(1.0f), position);
		m_scale = glm::scale(glm::mat4(1.0f), scale);
		m_localToWorld = m_translation * m_rotation * m_scale;
	}

	void UpdateRotation(float pitch, float yaw, float roll) {
		glm::quat qPitch = glm::angleAxis(glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::quat qYaw = glm::angleAxis(glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::quat qRoll = glm::angleAxis(glm::radians(roll), glm::vec3(0.0f, 0.0f, 1.0f));
		rotation = glm::normalize(qPitch * qYaw * qRoll);
	}

	void UpdateTransform() {
		m_translation = glm::translate(glm::mat4(1.0f), position);
		m_scale = glm::scale(glm::mat4(1.0f), scale);
		m_rotation = glm::mat4_cast(rotation);
	}
};*/

#endif
