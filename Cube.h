#ifndef CUBE_H
#define CUBE_H
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
	struct Cube : CollisionShape {

		/*std::array<glm::vec3, 8> m_vertices = {
			glm::vec3(-0.5f,0.5f,0.5f), glm::vec3(0.5f,0.5f,0.5f),
			glm::vec3(0.5f,0.5f,-0.5f), glm::vec3(-0.5f,0.5f,-0.5f),
			glm::vec3(-0.5f,-0.5f,0.5f), glm::vec3(0.5f,-0.5f,0.5f),
			glm::vec3(0.5f,-0.5f,-0.5f), glm::vec3(-0.5f,-0.5f,-0.5f)
		};*/
		/*std::array<Vertex, 8> vertices = {
			Vertex(glm::vec3(-0.5f,0.5f,0.5f), nullptr), Vertex(glm::vec3(0.5f,0.5f,0.5f),nullptr),
			Vertex(glm::vec3(0.5f,0.5f,-0.5f), nullptr), Vertex(glm::vec3(-0.5f,0.5f,-0.5f), nullptr),
			Vertex(glm::vec3(-0.5f,-0.5f,0.5f), nullptr), Vertex(glm::vec3(0.5f,-0.5f,0.5f), nullptr),
			Vertex(glm::vec3(0.5f,-0.5f,-0.5f), nullptr), Vertex(glm::vec3(-0.5f,-0.5f,-0.5f), nullptr)
		};
		std::array<Plane, 6> planes = {
			Plane{}, Plane{}, Plane{}, Plane{}, Plane{}, Plane{}
		};
		std::array<HalfEdge, 24> edges = {
			HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{},
			HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{},
			HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{},
			HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{}
		};*/
		Cube() : CollisionShape{} {
			/*vertices = {
				Vertex(glm::vec3(-0.5f,0.5f,0.5f), nullptr), Vertex(glm::vec3(0.5f,0.5f,0.5f),nullptr),
				Vertex(glm::vec3(0.5f,0.5f,-0.5f), nullptr), Vertex(glm::vec3(-0.5f,0.5f,-0.5f), nullptr),
				Vertex(glm::vec3(-0.5f,-0.5f,0.5f), nullptr), Vertex(glm::vec3(0.5f,-0.5f,0.5f), nullptr),
				Vertex(glm::vec3(0.5f,-0.5f,-0.5f), nullptr), Vertex(glm::vec3(-0.5f,-0.5f,-0.5f), nullptr)
			};*/
			vertices = {
				Vertex(glm::vec3(-0.5f,0.5f,0.5f), nullptr), Vertex(glm::vec3(0.5f,0.5f,0.5f),nullptr),
				Vertex(glm::vec3(0.5f,0.5f,-0.5f), nullptr), Vertex(glm::vec3(-0.5f,0.5f,-0.5f), nullptr),
				Vertex(glm::vec3(-0.5f,-0.5f,0.5f), nullptr), Vertex(glm::vec3(-0.5f,-0.5f,-0.5f), nullptr),
				Vertex(glm::vec3(0.5f,-0.5f,-0.5f), nullptr), Vertex(glm::vec3(0.5f,-0.5f,0.5f), nullptr)
			};

			planes = {
				Plane{}, Plane{}, Plane{}, Plane{}, Plane{}, Plane{}
			};
			edges = {
				HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{},
				HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{},
				HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{},
				HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{}, HalfEdge{}
			};
			/*
			//planes
			planes[0].edge = &edges[0];
			planes[0].normal = glm::vec3(0.0f, 1.0f, 0.0f);
			planes[1].edge = &edges[4];
			planes[1].normal = glm::vec3(0.0f, -1.0f, 0.0f);
			planes[2].edge = &edges[8];
			planes[2].normal = glm::vec3(0.0f, 0.0f, 1.0f);
			planes[3].edge = &edges[12];
			planes[3].normal = glm::vec3(0.0f, 0.0f, -1.0f);
			planes[4].edge = &edges[16];
			planes[4].normal = glm::vec3(1.0f, 0.0f, 0.0f);
			planes[5].edge = &edges[20];
			planes[5].normal = glm::vec3(-1.0f, 0.0f, 0.0f);
			
			//vertices
			vertices[0].edge = &edges[0];
			vertices[1].edge = &edges[1];
			vertices[2].edge = &edges[2];
			vertices[3].edge = &edges[3];
			vertices[4].edge = &edges[5];
			vertices[5].edge = &edges[4];
			vertices[6].edge = &edges[7];
			vertices[7].edge = &edges[6];
			//edges
			//top
			edges[0].index = 0;
			edges[0].origin = &vertices[0];
			edges[0].incident_face = &planes[0];
			edges[0].twin = &edges[8];
			edges[0].previous = &edges[3];
			edges[0].next = &edges[1];
			edges[1].index = 1;
			edges[1].origin = &vertices[1];
			edges[1].incident_face = &planes[0];
			edges[1].twin = &edges[16];
			edges[1].previous = &edges[0];
			edges[1].next = &edges[2];
			edges[2].index = 2;
			edges[2].origin = &vertices[2];
			edges[2].incident_face = &planes[0];
			edges[2].twin = &edges[12];
			edges[2].previous = &edges[1];
			edges[2].next = &edges[3];
			edges[3].index = 3;
			edges[3].origin = &vertices[3];
			edges[3].incident_face = &planes[0];
			edges[3].twin = &edges[20];
			edges[3].previous = &edges[2];
			edges[3].next = &edges[0];
			//bottom
			edges[4].index = 4;
			edges[4].origin = &vertices[5];
			edges[4].incident_face = &planes[1];
			edges[4].twin = &edges[10];
			edges[4].previous = &edges[7];
			edges[4].next = &edges[5];
			edges[5].index = 5;
			edges[5].origin = &vertices[4];
			edges[5].incident_face = &planes[1];
			edges[5].twin = &edges[22];
			edges[5].previous = &edges[4];
			edges[5].next = &edges[6];
			edges[6].index = 6;
			edges[6].origin = &vertices[7];
			edges[6].incident_face = &planes[1];
			edges[6].twin = &edges[14];
			edges[6].previous = &edges[5];
			edges[6].next = &edges[7];
			edges[7].index = 7;
			edges[7].origin = &vertices[6];
			edges[7].incident_face = &planes[1];
			edges[7].twin = &edges[18];
			edges[7].previous = &edges[6];
			edges[7].next = &edges[4];
			//front
			edges[8].index = 8;
			edges[8].origin = &vertices[1];
			edges[8].incident_face = &planes[2];
			edges[8].twin = &edges[0];
			edges[8].previous = &edges[11];
			edges[8].next = &edges[9];
			edges[9].index = 9;
			edges[9].origin = &vertices[0];
			edges[9].incident_face = &planes[2];
			edges[9].twin = &edges[23];
			edges[9].previous = &edges[8];
			edges[9].next = &edges[10];
			edges[10].index = 10;
			edges[10].origin = &vertices[4];
			edges[10].incident_face = &planes[2];
			edges[10].twin = &edges[4];
			edges[10].previous = &edges[9];
			edges[10].next = &edges[11];
			edges[11].index = 11;
			edges[11].origin = &vertices[5];
			edges[11].incident_face = &planes[2];
			edges[11].twin = &edges[17];
			edges[11].previous = &edges[10];
			edges[11].next = &edges[8];
			//back
			edges[12].index = 12;
			edges[12].origin = &vertices[3];
			edges[12].incident_face = &planes[3];
			edges[12].twin = &edges[2];
			edges[12].previous = &edges[15];
			edges[12].next = &edges[13];
			edges[13].index = 13;
			edges[13].origin = &vertices[2];
			edges[13].incident_face = &planes[3];
			edges[13].twin = &edges[19];
			edges[13].previous = &edges[12];
			edges[13].next = &edges[14];
			edges[14].index = 14;
			edges[14].origin = &vertices[6];
			edges[14].incident_face = &planes[3];
			edges[14].twin = &edges[6];
			edges[14].previous = &edges[13];
			edges[14].next = &edges[15];
			edges[15].index = 15;
			edges[15].origin = &vertices[7];
			edges[15].incident_face = &planes[3];
			edges[15].twin = &edges[21];
			edges[15].previous = &edges[14];
			edges[15].next = &edges[12];
			//right
			edges[16].index = 16;
			edges[16].origin = &vertices[2];
			edges[16].incident_face = &planes[4];
			edges[16].twin = &edges[1];
			edges[16].previous = &edges[19];
			edges[16].next = &edges[17];
			edges[17].index = 17;
			edges[17].origin = &vertices[1];
			edges[17].incident_face = &planes[4];
			edges[17].twin = &edges[11];
			edges[17].previous = &edges[16];
			edges[17].next = &edges[18];
			edges[18].index = 18;
			edges[18].origin = &vertices[5];
			edges[18].incident_face = &planes[4];
			edges[18].twin = &edges[7];
			edges[18].previous = &edges[17];
			edges[18].next = &edges[19];
			edges[19].index = 19;
			edges[19].origin = &vertices[6];
			edges[19].incident_face = &planes[4];
			edges[19].twin = &edges[13];
			edges[19].previous = &edges[18];
			edges[19].next = &edges[16];
			//left
			edges[20].index = 20;
			edges[20].origin = &vertices[0];
			edges[20].incident_face = &planes[5];
			edges[20].twin = &edges[3];
			edges[20].previous = &edges[23];
			edges[20].next = &edges[21];
			edges[21].index = 21;
			edges[21].origin = &vertices[3];
			edges[21].incident_face = &planes[5];
			edges[21].twin = &edges[15];
			edges[21].previous = &edges[20];
			edges[21].next = &edges[22];
			edges[22].index = 22;
			edges[22].origin = &vertices[7];
			edges[22].incident_face = &planes[5];
			edges[22].twin = &edges[5];
			edges[22].previous = &edges[21];
			edges[22].next = &edges[23];
			edges[23].index = 23;
			edges[23].origin = &vertices[4];
			edges[23].incident_face = &planes[5];
			edges[23].twin = &edges[9];
			edges[23].previous = &edges[22];
			edges[23].next = &edges[20];*/

			//planes
			planes[0].edge = &edges[0];
			planes[0].normal = glm::vec3(0.0f, 1.0f, 0.0f);
			planes[1].edge = &edges[4];
			planes[1].normal = glm::vec3(0.0f, -1.0f, 0.0f);
			planes[2].edge = &edges[8];
			planes[2].normal = glm::vec3(0.0f, 0.0f, 1.0f);
			planes[3].edge = &edges[12];
			planes[3].normal = glm::vec3(0.0f, 0.0f, -1.0f);
			planes[4].edge = &edges[16];
			planes[4].normal = glm::vec3(-1.0f, 0.0f, 0.0f);
			planes[5].edge = &edges[20];
			planes[5].normal = glm::vec3(1.0f, 0.0f, 0.0f);

			//vertices
			vertices[0].edge = &edges[0];
			vertices[1].edge = &edges[1];
			vertices[2].edge = &edges[2];
			vertices[3].edge = &edges[3];
			vertices[4].edge = &edges[5];
			vertices[5].edge = &edges[6];
			vertices[6].edge = &edges[7];
			vertices[7].edge = &edges[4];
			//edges
			//top
			edges[0].index = 0;
			edges[0].origin = &vertices[0];
			edges[0].incident_face = &planes[0];
			edges[0].twin = &edges[8];
			edges[0].previous = &edges[3];
			edges[0].next = &edges[1];
			edges[1].index = 1;
			edges[1].origin = &vertices[1];
			edges[1].incident_face = &planes[0];
			edges[1].twin = &edges[20];
			edges[1].previous = &edges[0];
			edges[1].next = &edges[2];
			edges[2].index = 2;
			edges[2].origin = &vertices[2];
			edges[2].incident_face = &planes[0];
			edges[2].twin = &edges[12];
			edges[2].previous = &edges[1];
			edges[2].next = &edges[3];
			edges[3].index = 3;
			edges[3].origin = &vertices[3];
			edges[3].incident_face = &planes[0];
			edges[3].twin = &edges[16];
			edges[3].previous = &edges[2];
			edges[3].next = &edges[0];
			//bottom
			edges[4].index = 4;
			edges[4].origin = &vertices[7];
			edges[4].incident_face = &planes[1];
			edges[4].twin = &edges[10];
			edges[4].previous = &edges[7];
			edges[4].next = &edges[5];
			edges[5].index = 5;
			edges[5].origin = &vertices[4];
			edges[5].incident_face = &planes[1];
			edges[5].twin = &edges[18];
			edges[5].previous = &edges[4];
			edges[5].next = &edges[6];
			edges[6].index = 6;
			edges[6].origin = &vertices[5];
			edges[6].incident_face = &planes[1];
			edges[6].twin = &edges[14];
			edges[6].previous = &edges[5];
			edges[6].next = &edges[7];
			edges[7].index = 7;
			edges[7].origin = &vertices[6];
			edges[7].incident_face = &planes[1];
			edges[7].twin = &edges[22];
			edges[7].previous = &edges[6];
			edges[7].next = &edges[4];
			//front
			edges[8].index = 8;
			edges[8].origin = &vertices[1];
			edges[8].incident_face = &planes[2];
			edges[8].twin = &edges[0];
			edges[8].previous = &edges[11];
			edges[8].next = &edges[9];
			edges[9].index = 9;
			edges[9].origin = &vertices[0];
			edges[9].incident_face = &planes[2];
			edges[9].twin = &edges[19];
			edges[9].previous = &edges[8];
			edges[9].next = &edges[10];
			edges[10].index = 10;
			edges[10].origin = &vertices[4];
			edges[10].incident_face = &planes[2];
			edges[10].twin = &edges[4];
			edges[10].previous = &edges[9];
			edges[10].next = &edges[11];
			edges[11].index = 11;
			edges[11].origin = &vertices[7];
			edges[11].incident_face = &planes[2];
			edges[11].twin = &edges[21];
			edges[11].previous = &edges[10];
			edges[11].next = &edges[8];
			//back
			edges[12].index = 12;
			edges[12].origin = &vertices[3];
			edges[12].incident_face = &planes[3];
			edges[12].twin = &edges[2];
			edges[12].previous = &edges[15];
			edges[12].next = &edges[13];
			edges[13].index = 13;
			edges[13].origin = &vertices[2];
			edges[13].incident_face = &planes[3];
			edges[13].twin = &edges[23];
			edges[13].previous = &edges[12];
			edges[13].next = &edges[14];
			edges[14].index = 14;
			edges[14].origin = &vertices[6];
			edges[14].incident_face = &planes[3];
			edges[14].twin = &edges[6];
			edges[14].previous = &edges[13];
			edges[14].next = &edges[15];
			edges[15].index = 15;
			edges[15].origin = &vertices[5];
			edges[15].incident_face = &planes[3];
			edges[15].twin = &edges[17];
			edges[15].previous = &edges[14];
			edges[15].next = &edges[12];
			//right
			edges[16].index = 16;
			edges[16].origin = &vertices[0];
			edges[16].incident_face = &planes[4];
			edges[16].twin = &edges[3];
			edges[16].previous = &edges[19];
			edges[16].next = &edges[17];
			edges[17].index = 17;
			edges[17].origin = &vertices[3];
			edges[17].incident_face = &planes[4];
			edges[17].twin = &edges[15];
			edges[17].previous = &edges[16];
			edges[17].next = &edges[18];
			edges[18].index = 18;
			edges[18].origin = &vertices[5];
			edges[18].incident_face = &planes[4];
			edges[18].twin = &edges[5];
			edges[18].previous = &edges[17];
			edges[18].next = &edges[19];
			edges[19].index = 19;
			edges[19].origin = &vertices[4];
			edges[19].incident_face = &planes[4];
			edges[19].twin = &edges[9];
			edges[19].previous = &edges[18];
			edges[19].next = &edges[16];
			//left
			edges[20].index = 20;
			edges[20].origin = &vertices[2];
			edges[20].incident_face = &planes[5];
			edges[20].twin = &edges[1];
			edges[20].previous = &edges[23];
			edges[20].next = &edges[21];
			edges[21].index = 21;
			edges[21].origin = &vertices[1];
			edges[21].incident_face = &planes[5];
			edges[21].twin = &edges[11];
			edges[21].previous = &edges[20];
			edges[21].next = &edges[22];
			edges[22].index = 22;
			edges[22].origin = &vertices[7];
			edges[22].incident_face = &planes[5];
			edges[22].twin = &edges[7];
			edges[22].previous = &edges[21];
			edges[22].next = &edges[23];
			edges[23].index = 23;
			edges[23].origin = &vertices[6];
			edges[23].incident_face = &planes[5];
			edges[23].twin = &edges[13];
			edges[23].previous = &edges[22];
			edges[23].next = &edges[20];
		}
		
	};
}
#endif
