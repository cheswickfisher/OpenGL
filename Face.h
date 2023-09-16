#ifndef FACE_H
#define FACE_H

#include <array>
#include <glm\glm\glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>
class Face {
public:
	glm::vec3 normal;
	glm::vec3 dimensions;
	std::array<int, 4> connected_faces;
	std::array<int, 4> vertices;
	
	Face() {
		normal = glm::vec3(0.0f);
		dimensions = glm::vec3(0.0f);
		connected_faces = { 0,0,0,0 };
		vertices = {};
	}

	Face(glm::vec3 _normal, glm::vec3 _dimensions, std::array<int, 4> _face_indices, std::array<int, 4> _vertices) {
		normal = _normal;
		dimensions = _dimensions;
		connected_faces = _face_indices;
		vertices = _vertices;
	}
};



#endif
