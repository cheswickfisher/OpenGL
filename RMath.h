#ifndef RMath_H
#define RMath_H
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include <glm/glm/gtc/matrix_access.hpp>

namespace WIP_Polygon {
	class RMath {
		public:
			static void ConstructBasisFromForward(glm::vec3 _forward, glm::vec3& _right, glm::vec3& _up);
	};
}
#endif