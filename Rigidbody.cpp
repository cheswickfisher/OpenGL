#include "Rigidbody.h"

namespace WIP_Polygon {
	Rigidbody::Rigidbody()
		: GameObject{},
		moveDirection(glm::vec3(0.0f)), collider{ /*new WIP_Polygon::BoxCollider{}*/ nullptr }
	{
	}
	Rigidbody::Rigidbody(glm::vec3 _scale, WIP_Polygon::Collider* _col)
		: GameObject{ _scale },
		moveDirection(glm::vec3(0.0f)), collider{ _col }
	{
	}
	Rigidbody::Rigidbody(glm::vec3 _scale, glm::vec3 _position, WIP_Polygon::Collider* _col)
		: GameObject{ _scale, _position },
		moveDirection(glm::vec3(0.0f)), collider{ _col }
	{
	}
	Rigidbody::Rigidbody(glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation, WIP_Polygon::Collider* _col)
		: GameObject{ _scale, _position, _rotation },
		moveDirection(glm::vec3(0.0f)), collider{ _col }
	{
	}
	void Rigidbody::UpdatePosition(glm::vec3 _position) {
		moveDirection = glm::normalize(_position - position);
		position = _position;
	}

}