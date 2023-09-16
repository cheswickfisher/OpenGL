#include "Vertex.h"
#include "HalfEdge.h"
namespace WIP_Polygon {
	Vertex::Vertex() :
	position{glm::vec3(0.0f)},
	edge{nullptr}
	{}
	Vertex::Vertex(glm::vec3 _position, HalfEdge* _edge) :
		position{_position},
		edge{_edge}
	{}
}
