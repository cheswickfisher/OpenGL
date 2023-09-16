#ifndef CharacterControls_H
#define CharacterControls_H

//#include "Camera.h"
//#include "AABB.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include <vector>
#include <glm\glm\glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>

class CharacterControls : public GameObject {
public:
	WIP_Polygon::Collider* collider;
	std::vector<float>this_is_error{};
	float moveSpeed;
	glm::vec3 moveDirection;
	float turnSpeed;
	CharacterControls() :
		GameObject{},
		collider{ new WIP_Polygon::BoxCollider() }
	{
		moveSpeed = 1.0f;
		moveDirection = glm::vec3(0.0f);
		turnSpeed = 1.0f;
		pitch = 0.0f;
		yaw = 0.0f;
		roll = 0.0f;
	}
	CharacterControls(glm::vec3 _scale, WIP_Polygon::Collider* _collider)
		: GameObject{ _scale },
		collider{ _collider }, moveSpeed(1.0f), moveDirection(glm::vec3(0.0f)), turnSpeed(1.0f)
	{}

	CharacterControls(glm::vec3 _scale, glm::vec3 _position, WIP_Polygon::Collider* _collider)
		: GameObject{ _scale, _position },
		collider{ _collider }, moveSpeed(1.0f), moveDirection(glm::vec3(0.0f)), turnSpeed(1.0f)
	{}

	CharacterControls(glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation, WIP_Polygon::Collider* _collider)
		: GameObject{ _scale, _position, _rotation },
		collider{ _collider }, moveSpeed(1.0f), moveDirection(glm::vec3(0.0f)), turnSpeed(1.0f)
	{}

};
#endif
