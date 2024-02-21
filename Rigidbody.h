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
		glm::vec3 moveDirection; //not using this for anything important
		glm::vec3 velocity;
		glm::vec3 acceleration;
		float mass;
		Rigidbody();
		Rigidbody(glm::vec3 _scale, float _mass, WIP_Polygon::Collider* _col);
		Rigidbody(glm::vec3 _scale, glm::vec3 _position, float _mass, WIP_Polygon::Collider* _col);
		Rigidbody(glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation, float _mass, WIP_Polygon::Collider* _col);
		void UpdatePosition(glm::vec3 _position);
		void AddForce(float force, glm::vec3 direction);
	};
}
#endif