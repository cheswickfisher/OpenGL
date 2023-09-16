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
	class QuadCollider : public Collider{
	public:
		WIP_Polygon::Quad quad{};
		QuadCollider() :
			Collider{ glm::vec3(1.0f), glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 0.0f) },
			quad{WIP_Polygon::Quad()}
		{
			collider = &quad;
		}
		QuadCollider(glm::vec3 _scale) :
			Collider{ _scale, glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 0.0f) },
			quad{ WIP_Polygon::Quad() }
		{
			collider = &quad;
		}
		QuadCollider(glm::vec3 _scale, glm::vec3 _position) :
			Collider{ _scale, _position, glm::vec3(0.0f, 0.0f, 0.0f) },
			quad{ WIP_Polygon::Quad() } 
		{
			collider = &quad;
		}
		QuadCollider(glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation) :
			Collider{ _scale, _position, _rotation },
			quad{ WIP_Polygon::Quad() }
		{
			collider = &quad;
		}

		void DrawAxes() override {

		}
	};
}
#endif
