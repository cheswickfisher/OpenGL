#ifndef OBJIMPORTER_H
#define OBJIMPORTER_H
#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>
#include <glm\glm\gtc\quaternion.hpp>
#include <glm\glm\gtx\quaternion.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include "OBJMesh.h"

namespace WIP_Polygon {
	class OBJImporter {
	public:
		static void split(const std::string& in,
			std::vector<std::string>& out,
			std::string token);

		static OBJMesh Import(std::string file_path);
	};
}
#endif
