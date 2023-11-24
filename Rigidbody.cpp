#include "Rigidbody.h"

namespace WIP_Polygon {
	Rigidbody::Rigidbody()
		: GameObject{},
		moveDirection(glm::vec3(0.0f)), mass{0.0f}, collider { /*new WIP_Polygon::BoxCollider{}*/ nullptr
	}
	{
	}
	Rigidbody::Rigidbody(glm::vec3 _scale, float _mass, WIP_Polygon::Collider* _col)
		: GameObject{ _scale },
		moveDirection(glm::vec3(0.0f)), mass{ _mass }, collider {
		_col
	}
	{
	}
	Rigidbody::Rigidbody(glm::vec3 _scale, glm::vec3 _position, float _mass, WIP_Polygon::Collider* _col)
		: GameObject{ _scale, _position },
		moveDirection(glm::vec3(0.0f)), mass{ _mass }, collider {
		_col
	}
	{
	}
	Rigidbody::Rigidbody(glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation, float _mass, WIP_Polygon::Collider* _col)
		: GameObject{ _scale, _position, _rotation },
		moveDirection(glm::vec3(0.0f)), mass{ _mass }, collider {
		_col
	}
	{
	}
	void Rigidbody::UpdatePosition(glm::vec3 _position) {
		moveDirection = glm::normalize(_position - position);
		position = _position;
	}

}