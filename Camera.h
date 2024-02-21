#ifndef Camera_H
#define Camera_H

#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include <glm/glm/gtc/matrix_access.hpp>

#include "Preferences.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace WIP_Polygon {
	class Camera {
	private:
		glm::vec3 cameraFront;
	public:
		float cameraSpeed;
		float sensitivity;
		float posOffset;
		float pitch;
		float yaw;
		float fov;
		glm::quat cameraRot;
		glm::vec3 cameraPos;
		glm::vec3 worldUp;
		glm::vec3 forward;
		glm::mat4 view;
		glm::mat4 projection;

		Camera();
		void UpdateRotation();
		void UpdatePosition(glm::vec3 target);
		glm::mat4 ViewMatrix();
		glm::mat4 ProjectionMatrix();
		glm::vec3 Front();
	};

}

#endif