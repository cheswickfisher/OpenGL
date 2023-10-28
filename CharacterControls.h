#ifndef CharacterControls_H
#define CharacterControls_H

#include "Rigidbody.h"
#include <vector>
#include <glm\glm\glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>
namespace WIP_Polygon {
	class Collider;
	class CharacterControls : public Rigidbody {
	public:
		float moveSpeed;
		glm::vec3 moveDirection;
		float turnSpeed;
		CharacterControls();
		CharacterControls(glm::vec3 _scale, WIP_Polygon::Collider* _collider);
		CharacterControls(glm::vec3 _scale, glm::vec3 _position, WIP_Polygon::Collider* _collider);
		CharacterControls(glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation, WIP_Polygon::Collider* _collider);
	};
	/*class CharacterControls : public GameObject {
	public:
		WIP_Polygon::Collider* collider;
		float moveSpeed;
		glm::vec3 moveDirection;
		float turnSpeed;
		CharacterControls();
		CharacterControls(glm::vec3 _scale, WIP_Polygon::Collider* _collider);
		CharacterControls(glm::vec3 _scale, glm::vec3 _position, WIP_Polygon::Collider* _collider);
		CharacterControls(glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation, WIP_Polygon::Collider* _collider);
	};*/
}
#endif
