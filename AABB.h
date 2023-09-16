#ifndef AABB_H
#define AABB_H

#include <array>
#include <glm/glm/glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>

class AABB {
private:
	std::array<glm::vec3, 8> corners;
	glm::mat4 translation;
	glm::mat4 scale;
public:
	glm::vec3 center;
	glm::vec3 radius;
	glm::vec3 velocity;
	bool stationary;
	float sideLength;
	float minX;
	float maxX;
	float minY;
	float maxY;
	float minZ;
	float maxZ;

	AABB() {
		sideLength = 1.0f;
		corners = { glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, -0.5f),
					glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, -0.5f),glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec3(-0.5f, -0.5f, -0.5f),
		};
		center = glm::vec3(0.0f);
		radius = glm::vec3(1.0f);
		translation = glm::mat4(1.0f);
		scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
		velocity = glm::vec3(0.0f);
		stationary = true;
		minX = -0.5f;
		maxX = 0.5f;
		minY = -0.5f;
		maxY = 0.5f;
		minZ = -0.5f;
		maxZ = 0.5f;
	}

	AABB(float _sideLength, glm::vec3 _position)
	{
		sideLength = _sideLength;
		corners = { glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, -0.5f),
					glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, -0.5f),glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec3(-0.5f, -0.5f, -0.5f),
		};
		center = _position;
		radius = glm::vec3(_sideLength * .5f);
		translation = glm::translate(glm::mat4(1.0f), _position);
		scale = glm::scale(glm::mat4(1.0f), glm::vec3(sideLength));
		velocity = glm::vec3(0.0f);
		stationary = true;
		minX = -0.5f * sideLength;
		maxX = 0.5f * sideLength;
		minY = -0.5f * sideLength;
		maxY = 0.5f * sideLength;
		minZ = -0.5f * sideLength;
		maxZ = 0.5f * sideLength;
	}

	std::array<glm::vec4, 8> CornersWorld() {
		translation = glm::translate(glm::mat4(1.0f), center);
		std::array<glm::vec4, 8> c;
		for (unsigned int i = 0; i < 8; i++) {
			c[i] = translation * scale * glm::vec4(corners[i].x, corners[i].y, corners[i].z, 1.0f);
		}
		return c;
	}
};
#endif
