#ifndef QUADCOLLIDER_H
#define QUADCOLLIDER_H
#include <array>
#include <vector>
#include <glm/glm/glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include "AABB.h"
#include "Cube.h"
#include "Quad.h"
#include "Collider.h"

namespace WIP_Polygon {
	class Collider;
	class QuadCollider : public Collider{
	public:
		WIP_Polygon::Quad quad;
		QuadCollider();
		QuadCollider(glm::vec3 _scale);
		QuadCollider(glm::vec3 _scale, glm::vec3 _position);
		QuadCollider(glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation);		
		void DrawAxes() override;
		glm::mat3 CalculateInertiaTensor() override;
	};
}
#endif
