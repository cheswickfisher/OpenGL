#ifndef HALFEDGE_H
#define HALFEDGE_H
#include <glm\glm\glm.hpp>
#include "Vertex.h"
#include "Plane.h"
#include <vector>
namespace WIP_Polygon {
	struct Vertex;
	struct Plane;
	struct HalfEdge {
		int index;
		Vertex* origin;
		Plane* incident_face;
		//Plane* incident_face_b;
		HalfEdge* twin;
		HalfEdge* previous;
		HalfEdge* next;
		HalfEdge();
		glm::vec3 Direction();
		bool operator!=(const HalfEdge& other) {
			return this->index != other.index;
		}
	};
}
#endif


