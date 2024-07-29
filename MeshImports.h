#ifndef MESHIMPORTS_H
#define MESHIMPORTS_H
#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>
#include <glm\glm\gtc\quaternion.hpp>
#include <glm\glm\gtx\quaternion.hpp>
#include "OBJMesh.h"
#include "OBJImporter.h"
#include <vector>
#include <string>

namespace WIP_Polygon {
	class MeshImports {
	public:
		static OBJMesh test_cube;
		static OBJMesh unit_cube;
		static OBJMesh little_ship;
	};
}
#endif
