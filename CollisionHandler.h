#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H
#include "AABB.h"
#include "BoxCollider.h"
#include "Face.h"
#include "Debug.h"
#include "Colors.h"
#include "PlaneQuery.h"
#include "EdgeQuery.h"
#include "HalfEdge.h"
#include "Vertex.h"
#include "Plane.h"
#include "Cube.h"
#include "Quad.h"
#include "Manifold.h"
#include "Scene.h"
#include "glm\glm\glm.hpp"
#include <glm\glm\gtc\type_ptr.hpp>
#include <glm\glm\gtc\quaternion.hpp>
#include <glm\glm\gtx\quaternion.hpp>
#include <iostream>

#define PLANE_THICKNESS_EPSILON 0.0001f
#define POINT_IN_FRONT_OF_PLANE 0
#define POINT_BEHIND_PLANE 1
#define POINT_ON_PLANE 2
#define IDENTITY_QUAT glm::quat(1.0f,0.0f,0.0f,0.0f)
namespace WIP_Polygon {
	class Scene;
	class CollisionHandler {

	public:
		const float EPSILON = 0.001f;
		const float EPSILONB = 0.01f;
		const float PARALLEL = 0.99f;

		float Distance(WIP_Polygon::HalfEdge edge_a, WIP_Polygon::HalfEdge edge_b, WIP_Polygon::Collider* a, WIP_Polygon::Collider* b, glm::vec3& normal);

		float ClosestPtSegmentSegment(glm::vec3 p1, glm::vec3 q1, glm::vec3 p2, glm::vec3 q2, float& s, float& t, glm::vec3& c1, glm::vec3& c2);

		bool BuildMinkowskiFace(WIP_Polygon::Collider* a, WIP_Polygon::Collider* b, WIP_Polygon::HalfEdge edge_a, WIP_Polygon::HalfEdge edge_b);

		bool IsMinkowskiFace(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, glm::vec3 ba, glm::vec3 dc);

		PlaneQuery QueryFaceDirections(WIP_Polygon::Collider* a, WIP_Polygon::Collider* b);

		EdgeQuery QueryEdgeDirections(WIP_Polygon::Collider* a, WIP_Polygon::Collider* b);

		bool Overlap(WIP_Polygon::Collider* a, WIP_Polygon::Collider* b, WIP_Polygon::ContactManifold& manifold);

		void ResolveCollisions(std::vector<std::pair <WIP_Polygon::AABB*, WIP_Polygon::AABB*>>& _aabb_pairs);

		void ResolveColliions2(std::vector<std::pair <WIP_Polygon::AABB*, WIP_Polygon::AABB*>>& _aabb_pairs);

		void UpdateSceneDynamicColliders(WIP_Polygon::Scene& scene);

		void UpdateSceneDynamicColliders2(WIP_Polygon::Scene& scene);

		void CreatePlaneContact(WIP_Polygon::Collider* a, WIP_Polygon::Collider* b, PlaneQuery query_A, PlaneQuery query_B, WIP_Polygon::ContactManifold& manifold);

		void CreateEdgeContact(WIP_Polygon::Collider* a, WIP_Polygon::Collider* b, EdgeQuery e, WIP_Polygon::ContactManifold& manifold);

		WIP_Polygon::Plane* FindIncidentPlane(WIP_Polygon::Collider* incident, WIP_Polygon::Collider* reference, PlaneQuery& plane_query);

		std::vector<glm::vec3> Intersect(glm::vec3 plane_origin, glm::vec3 plane_normal, glm::vec3 line_start, glm::vec3 line_end, std::vector<glm::vec3>in);

		int IntersectSegmentPlane(glm::vec3 a, glm::vec3 b, glm::vec3 plane_normal, glm::vec3 plane_point, float& t, glm::vec3& q);

		int ClassifyPointToPlane(glm::vec3 p, glm::vec3 plane_normal, glm::vec3 plane_point);

		WIP_Polygon::ContactManifold ClipPolygon(WIP_Polygon::Collider* incident, WIP_Polygon::Collider* reference, PlaneQuery plane_query);		

		void CheckPositions(std::vector<glm::vec3> v, glm::vec4 col, float size);

		void CheckLines(glm::vec3 origin, glm::vec3 end, glm::vec4 col);


		bool IsZeroVector(glm::vec3 v);

	};
}
#endif
