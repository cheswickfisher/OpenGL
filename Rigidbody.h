#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "GameObject.h"
#include <glm\glm\glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>

namespace WIP_Polygon {
	class Collider;
	class Rigidbody : public GameObject {
	public:
		WIP_Polygon::Collider* collider;
		glm::vec3 moveDirection;
		Rigidbody();
		Rigidbody(glm::vec3 _scale, WIP_Polygon::Collider* _col);
		Rigidbody(glm::vec3 _scale, glm::vec3 _position, WIP_Polygon::Collider* _col);
		Rigidbody(glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation, WIP_Polygon::Collider* _col);
		void UpdatePosition(glm::vec3 _position);
	};
}
#endif