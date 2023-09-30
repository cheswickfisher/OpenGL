#ifndef  QUAD_H
#define QUAD_H
#include <array>
#include "HalfEdge.h"
#include "Plane.h"
#include "Vertex.h"
#include "CollisionShape.h"
#include "glm\glm\glm.hpp"
#include <vector>
namespace WIP_Polygon {
	/*struct Vertex;
	struct Plane;
	struct HalfEdge;*/
	struct Quad : CollisionShape {
		/*std::array<Vertex, 4> vertices = {
			Vertex(glm::vec3(0.5f, 0.5f, 0.0f), nullptr), Vertex(glm::vec3(-0.5f, 0.5f, 0.0f),nullptr),
			Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), nullptr), Vertex(glm::vec3(0.5f, -0.5f, 0.0f), nullptr),
		};
		std::array<Plane, 2> planes = {
			Plane{}, Plane{}
		};
		std::array<HalfEdge, 8> edges = {
			HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{},
			HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{}
		};*/

		Quad() {
			vertices = {
				Vertex(glm::vec3(0.5f, 0.5f, 0.0f), nullptr), Vertex(glm::vec3(-0.5f, 0.5f, 0.0f),nullptr),
				Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), nullptr), Vertex(glm::vec3(0.5f, -0.5f, 0.0f), nullptr),
			};
			
			planes = {
				Plane{}, Plane{}
			};
		

			edges = {
				HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{},
				HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{}
			};

			//planes
			planes[0].edge = &edges[0];
			planes[0].normal = glm::vec3(0.0f, 0.0f, 1.0f);
			planes[1].edge = &edges[4];
			planes[1].normal = glm::vec3(0.0f, 0.0f, -1.0f);

			//vertices
			vertices[0].edge = &edges[0];
			vertices[1].edge = &edges[1];
			vertices[2].edge = &edges[2];
			vertices[3].edge = &edges[3];
			//edges
			edges[0].index = 0;
			edges[0].origin = &vertices[0];
			edges[0].incident_face = &planes[0];
			edges[0].twin = &edges[4];
			edges[0].previous = &edges[3];
			edges[0].next = &edges[1];
			edges[1].index = 1;
			edges[1].origin = &vertices[1];
			edges[1].incident_face = &planes[0];
			edges[1].twin = &edges[7];
			edges[1].previous = &edges[0];
			edges[1].next = &edges[2];
			edges[2].index = 2;
			edges[2].origin = &vertices[2];
			edges[2].incident_face = &planes[0];
			edges[2].twin = &edges[6];
			edges[2].previous = &edges[1];
			edges[2].next = &edges[3];
			edges[3].index = 3;
			edges[3].origin = &vertices[3];
			edges[3].incident_face = &planes[0];
			edges[3].twin = &edges[5];
			edges[3].previous = &edges[2];
			edges[3].next = &edges[0];
			edges[4].index = 4;
			edges[4].origin = &vertices[1];
			edges[4].incident_face = &planes[1];
			edges[4].twin = &edges[0];
			edges[4].previous = &edges[7];
			edges[4].next = &edges[5];
			edges[5].index = 5;
			edges[5].origin = &vertices[0];
			edges[5].incident_face = &planes[1];
			edges[5].twin = &edges[3];
			edges[5].previous = &edges[4];
			edges[5].next = &edges[6];
			edges[6].index = 6;
			edges[6].origin = &vertices[3];
			edges[6].incident_face = &planes[1];
			edges[6].twin = &edges[2];
			edges[6].previous = &edges[5];
			edges[6].next = &edges[7];
			edges[7].index = 7;
			edges[7].origin = &vertices[2];
			edges[7].incident_face = &planes[1];
			edges[7].twin = &edges[1];
			edges[7].previous = &edges[6];
			edges[7].next = &edges[4];
		}
		
	};
}

#endif

