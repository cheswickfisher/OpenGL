#ifndef PHYSICSHANDLER_H
#define PHYSICSHANDLER_H

#include "Rigidbody.h"

#include "glm\glm\glm.hpp"
#include <glm\glm\gtc\type_ptr.hpp>
#include <glm\glm\gtc\quaternion.hpp>
#include <glm\glm\gtx\quaternion.hpp>
#include <vector>

namespace WIP_Polygon {
	class PhysicsHandler {
		public:
			void ApplyForces(std::vector<Rigidbody*>*_rbs);
			void ClearForces(std::vector<Rigidbody*>* _rbs);
			PhysicsHandler();
	};
}

#endif
