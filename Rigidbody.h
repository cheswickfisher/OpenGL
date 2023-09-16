#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "GameObject.h"
#include "BoxCollider.h"
#include <glm\glm\glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>

class Rigidbody : public GameObject {
public:
	WIP_Polygon::Collider* collider;
	glm::vec3 moveDirection;

	Rigidbody()
		: GameObject{},
		moveDirection(glm::vec3(0.0f)), collider{ new WIP_Polygon::BoxCollider{} }
	{
	}

	Rigidbody(glm::vec3 _scale, WIP_Polygon::Collider* _col)
		: GameObject{_scale},
		 moveDirection(glm::vec3(0.0f)), collider{ _col }
	{
	}

	Rigidbody(glm::vec3 _scale, glm::vec3 _position, WIP_Polygon::Collider* _col)
		: GameObject{ _scale, _position },
		moveDirection(glm::vec3(0.0f)), collider{_col}
	{
	}

	void UpdatePosition(glm::vec3 _position) {
		moveDirection = glm::normalize(_position - position);
		position = _position;
	}

};

#endif