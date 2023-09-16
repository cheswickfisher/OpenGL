#ifndef PLANEQUERY_H
#define PLANEQUERY_H

struct PlaneQuery {
	float max_distance{};
	float min_penetration{};
	int max_index{};
	int min_index{};
};

#endif
