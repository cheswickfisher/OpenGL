#include "CharacterControls.h"

namespace WIP_Polygon {
	CharacterControls::CharacterControls() :
		moveSpeed{ 1.0f }, moveDirection{ glm::vec3(0.0f) },
		turnSpeed{ 1.0f }, Rigidbody{}
	{}
	CharacterControls::CharacterControls(glm::vec3 _scale, WIP_Polygon::Collider* _collider) :
		Rigidbody{ _scale , _collider},
		moveSpeed(1.0f), moveDirection(glm::vec3(0.0f)), turnSpeed(1.0f)
	{}
	CharacterControls::CharacterControls(glm::vec3 _scale, glm::vec3 _position, WIP_Polygon::Collider* _collider)
		: Rigidbody{ _scale, _position, _collider },
		 moveSpeed(1.0f), moveDirection(glm::vec3(0.0f)), turnSpeed(1.0f)
	{}

	CharacterControls::CharacterControls(glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation, WIP_Polygon::Collider* _collider)
		: Rigidbody{ _scale, _position, _rotation, _collider },
		moveSpeed(1.0f), moveDirection(glm::vec3(0.0f)), turnSpeed(1.0f)
	{}
	/*CharacterControls::CharacterControls() :
		moveSpeed{ 1.0f }, moveDirection{ glm::vec3(0.0f) },
		turnSpeed{ 1.0f }, GameObject{},
		collider{ new WIP_Polygon::BoxCollider() }
	{}
	CharacterControls::CharacterControls(glm::vec3 _scale, WIP_Polygon::Collider* _collider) :
		GameObject{ _scale }, collider{ _collider }, 
		moveSpeed(1.0f), moveDirection(glm::vec3(0.0f)), turnSpeed(1.0f)
	{}
	CharacterControls::CharacterControls(glm::vec3 _scale, glm::vec3 _position, WIP_Polygon::Collider* _collider)
		: GameObject{ _scale, _position },
		collider{ _collider }, moveSpeed(1.0f), moveDirection(glm::vec3(0.0f)), turnSpeed(1.0f)
	{}

	CharacterControls::CharacterControls(glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation, WIP_Polygon::Collider* _collider)
		: GameObject{ _scale, _position, _rotation },
		collider{ _collider }, moveSpeed(1.0f), moveDirection(glm::vec3(0.0f)), turnSpeed(1.0f)
	{}*/

}