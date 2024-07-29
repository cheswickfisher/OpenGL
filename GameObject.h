#ifndef  GAMEOBJECT_H
#define GAMEOBJECT_H
#include "MeshRenderer.h"
#include "Preferences.h"
#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>
#include <glm\glm\gtc\quaternion.hpp>
#include <glm\glm\gtx\quaternion.hpp>
#include <iostream>
#include <array>
#include <string>
namespace WIP_Polygon {
	class MeshRenderer;
	class GameObject {
	public:
		glm::vec3 position;
		glm::vec3 scale;
		glm::quat rotation;
		glm::mat4 m_localToWorld;
		float pitch;
		float yaw;
		float roll;
		float pitch_delta;
		float yaw_delta;
		float roll_delta;
		glm::vec3 move_delta;
		WIP_Polygon::MeshRenderer* mesh_renderer;
		bool is_static;
		std::string name;
		GameObject();
		GameObject(glm::vec3 _scale);
		GameObject(glm::vec3 _scale, glm::vec3 _position);
		GameObject(glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation);
		glm::vec3 Forward();
		glm::vec3 Right();
		glm::vec3 Up();
		void UpdatePosition();
		void UpdateRotation();
		virtual void UpdateTransform();
	};
}
#endif

