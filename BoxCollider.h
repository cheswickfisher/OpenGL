#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <array>
#include <vector>
#include <string>
#include <glm/glm/glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include "Face.h"
#include "Cube.h"
#include "Collider.h"

namespace WIP_Polygon {
	class Collider;
	class BoxCollider : public Collider {
	public:
		WIP_Polygon::Cube cube;
		BoxCollider();
		BoxCollider(glm::vec3 _scale);
		BoxCollider(glm::vec3 _scale, glm::vec3 _position);
		BoxCollider(glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation);
		void DrawAxes() override;
	};
}
#endif