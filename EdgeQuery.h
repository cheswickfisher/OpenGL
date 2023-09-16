#ifndef EDGEQUERY_H
#define EDGEQUERY_H
#include <glm\glm\glm.hpp>

struct EdgeQuery {
	float max_distance{};
	float min_distance{};
	int max_edge_a{};
	int max_edge_b{};
	int min_edge_a{};
	int min_edge_b{};
	glm::vec3 edge_normal{};
};
#endif
