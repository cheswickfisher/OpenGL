#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H
#include "AABB.h"
#include "BoxCollider.h"
#include "Face.h"
#include "Debug.h"
#include "Colors.h"
#include "Query.h"
#include "EdgeQuery.h"
#include "HalfEdge.h"
#include "Vertex.h"
#include "Plane.h"
#include "Cube.h"
#include "Quad.h"
#include "Manifold.h"
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

class CollisionHandler {
public:
	const float EPSILON = 0.001f;
	const float EPSILONB = 0.01f;
	const float PARALLEL = 0.99f;
	bool Intersect(AABB a, AABB b) {
			return 
				a.minX <= b.maxX &&
				a.maxX >= b.minX &&
				a.minY <= b.maxY &&
				a.maxY >= b.minY &&
				a.minZ <= b.maxZ &&
				a.maxZ >= b.minZ;
	}

	glm::vec3 SeparatingAxis(AABB a, AABB b) {
		glm::vec3 yAxis = glm::normalize(glm::vec3(0.0f, a.center.y - b.center.y, 0.0f));
		glm::vec3 xAxis = glm::normalize(glm::vec3(a.center.x - b.center.x, 0.0f, 0.0f));
		glm::vec3 zAxis = glm::normalize(glm::vec3(0.0f, 0.0f, a.center.z - b.center.z));

		float aminx = a.center.x - a.radius.x;
		float amaxx = a.center.x + a.radius.x;
		float bminx = b.center.x - b.radius.x;
		float bmaxx = b.center.x + b.radius.x;

		float aminy = a.center.y - a.radius.y;
		float amaxy = a.center.y + a.radius.y;
		float bminy = b.center.y - b.radius.y;
		float bmaxy = b.center.y + b.radius.y;

		float aminz = a.center.z - a.radius.z;
		float amaxz = a.center.z + a.radius.z;
		float bminz = b.center.z - b.radius.z;
		float bmaxz = b.center.z + b.radius.z;

		float xOverlap{ 0.0f };
		float yOverlap{ 0.0f };
		float zOverlap{ 0.0f };
		float minOverlap = std::numeric_limits<float>::infinity();
		glm::vec3 contactNormal = glm::vec3(0.0f);
		if (aminx <= bmaxx &&
			amaxx >= bminx) {
			xOverlap = std::min(std::abs(amaxx - bminx), std::abs(aminx - bmaxx));
			std::cout << "xOverlap :" << xOverlap << "\n";
			if (xOverlap < minOverlap) { minOverlap = xOverlap; contactNormal = xAxis; }
		}
		else { return glm::vec3(0.0f); }
		if (aminy <= bmaxy &&
			amaxy >= bminy) {
			yOverlap = std::min(std::abs(amaxy - bminy), std::abs(aminy - bmaxy));
			std::cout << "yOverlap :" << yOverlap << "\n";
			if (yOverlap < minOverlap) {  minOverlap = yOverlap; contactNormal = yAxis; }
		}
		else { return glm::vec3(0.0f); }
		if (aminz <= bmaxz &&
			amaxz >= bminz) {
			zOverlap = std::min(std::abs(amaxz - bminz), std::abs(aminz - bmaxz));
			std::cout << "zOverlap :" << zOverlap << "\n";
			if (zOverlap < minOverlap) { minOverlap = zOverlap ; contactNormal = zAxis; }
		}
		else { return glm::vec3(0.0f); }
		//std::cout << "minOverlap: " << minOverlap << "\n";
		//std::cout << "CONTACTNORMAL: " << contactNormal.x << "," << contactNormal.y << "," << contactNormal.z << "\n";
		if (minOverlap == std::numeric_limits<float>::infinity()) { minOverlap = 0; }
		return contactNormal * minOverlap;
	}


	glm::vec3 TestOBBOBB_3(WIP_Polygon::BoxCollider a, WIP_Polygon::BoxCollider b) {
		float ra{};
		float rb{};
		glm::mat3 R;
		glm::mat3 AbsR;
		float t_distance{};
		float penetration{};
		float max_penetration = -std::numeric_limits<float>::infinity();
		glm::vec3 contact_axis = glm::vec3(0.0f);

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				R[i][j] = glm::dot(a.u[i], b.u[j]);
			}
		}

		glm::vec3 t = b.center - a.center;
		t = glm::vec3(glm::dot(t, a.u[0]), glm::dot(t, a.u[1]), glm::dot(t, a.u[2]));
		
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				AbsR[i][j] = glm::abs(R[i][j]) + EPSILON;
			}
		}
		//Ax, Ay, Az
		for (int i = 0; i < 3; i++) {
			ra = a.e[i];
			rb = b.e[0] * AbsR[i][0] + b.e[1] * AbsR[i][1] + b.e[2] * AbsR[i][2];
			t_distance = glm::abs(t[i]);
			penetration = t_distance - rb - ra;
			if (!CheckCollision2(penetration, max_penetration, a.u[i], contact_axis)) { return glm::vec3(0.0f); }
		}
		//Bx, By, Bz
		for (int i = 0; i < 3; i++) {
			ra = a.e[0] * AbsR[0][i] + a.e[1] * AbsR[1][i] + a.e[2] * AbsR[2][i];
			rb = b.e[i];
			t_distance = glm::abs(t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i]);
			penetration = t_distance - rb - ra;
			if (!CheckCollision2(penetration, max_penetration, b.u[i], contact_axis)) { return glm::vec3(0.0f); }
		}
		/*
		//Ax X Bx
		ra = a.e[1] * AbsR[2][0] + a.e[2] * AbsR[1][0];
		rb = b.e[1] * AbsR[0][2] + b.e[2] * AbsR[0][1];
		t_distance = glm::abs(t[2] * R[1][0] - t[1] * R[2][0]);
		penetration = t_distance - rb - ra;
		if (!CheckCollision2(penetration, max_penetration, glm::normalize(glm::cross(a.u[0], b.u[0])), contact_axis)) { return glm::vec3(0.0f); }
		//Ax X By
		ra = a.e[0] * AbsR[2][0] + a.e[2] * AbsR[0][0];
		rb = b.e[1] * AbsR[1][2] + b.e[2] * AbsR[1][1];
		t_distance = glm::abs(t[0] * R[2][0] - t[2] * R[0][0]);
		penetration = t_distance - rb - ra;
		if (!CheckCollision2(penetration, max_penetration, glm::normalize(glm::cross(a.u[0], b.u[1])), contact_axis)) { return glm::vec3(0.0f); }
		//Ax X Bz
		ra = a.e[1] * AbsR[2][2] + a.e[2] * AbsR[1][2];
		rb = b.e[0] * AbsR[0][1] + b.e[1] * AbsR[0][0];
		t_distance = glm::abs(t[2] * R[1][2] - t[1] * R[2][2]);
		penetration = t_distance - rb - ra;
		if (!CheckCollision2(penetration, max_penetration, glm::normalize(glm::cross(a.u[0], b.u[2])), contact_axis)) { return glm::vec3(0.0f); }
		//Ay X Bx
		ra = a.e[0] * AbsR[2][0] + a.e[2] * AbsR[0][0];
		rb = b.e[1] * AbsR[1][2] + b.e[2] * AbsR[1][1];
		t_distance = glm::abs(t[0] * R[2][0] - t[2] * R[0][0]);
		penetration = t_distance - rb - ra;
		if (!CheckCollision2(penetration, max_penetration, glm::normalize(glm::cross(a.u[1], b.u[0])), contact_axis)) { return glm::vec3(0.0f); }
		//Ay X By
		ra = a.e[0] * AbsR[2][1] + a.e[2] * AbsR[0][1];
		rb = b.e[0] * AbsR[1][2] + b.e[2] * AbsR[1][0];
		t_distance = glm::abs(t[0] * R[2][1] - t[2] * R[0][1]);
		penetration = t_distance - rb - ra;
		if (!CheckCollision2(penetration, max_penetration, glm::normalize(glm::cross(a.u[1], b.u[1])), contact_axis)) { return glm::vec3(0.0f); }
		//Ay X Bz
		ra = a.e[0] * AbsR[2][2] + a.e[2] * AbsR[0][2];
		rb = b.e[0] * AbsR[1][1] + b.e[1] * AbsR[1][0];
		t_distance = glm::abs(t[0] * R[2][2] - t[2] * R[0][2]);
		penetration = t_distance - rb - ra;
		if (!CheckCollision2(penetration, max_penetration, glm::normalize(glm::cross(a.u[1], b.u[2])), contact_axis)) { return glm::vec3(0.0f); }
		//Az X Bx
		ra = a.e[0] * AbsR[1][0] + a.e[1] * AbsR[0][0];
		rb = b.e[1] * AbsR[2][2] + b.e[2] * AbsR[2][1];
		t_distance = glm::abs(t[1] * R[0][0] - t[0] * R[1][0]);
		penetration = t_distance - rb - ra;
		if (!CheckCollision2(penetration, max_penetration, glm::normalize(glm::cross(a.u[2], b.u[0])), contact_axis)) { return glm::vec3(0.0f); }
		//Az X By
		ra = a.e[0] * AbsR[1][1] + a.e[1] * AbsR[0][1];
		rb = b.e[0] * AbsR[2][2] + b.e[2] * AbsR[2][0];
		t_distance = glm::abs(t[1] * R[0][1] - t[0] * R[1][1]);
		penetration = t_distance - rb - ra;
		if (!CheckCollision2(penetration, max_penetration, glm::normalize(glm::cross(a.u[2], b.u[1])), contact_axis)) { return glm::vec3(0.0f); }
		//Az X Bz
		ra = a.e[0] * AbsR[1][2] + a.e[1] * AbsR[0][2];
		rb = b.e[0] * AbsR[2][1] + b.e[1] * AbsR[2][0];
		t_distance = glm::abs(t[1] * R[0][2] - t[0] * R[1][2]);
		penetration = t_distance - rb - ra;
		if (!CheckCollision2(penetration, max_penetration, glm::normalize(glm::cross(a.u[2], b.u[2])), contact_axis)) { return glm::vec3(0.0f); }
		*/
		float length = glm::length(contact_axis);
		if (length == 0.0f) {
			return contact_axis * 0.0f;
		}

		else {
			contact_axis = glm::normalize(contact_axis * glm::dot(contact_axis, a.center - b.center));

			glm::vec3 offset = contact_axis * glm::abs(max_penetration);
			glm::vec3 contact_normal = glm::normalize(offset);
			return offset;
		}
	}
	


	float Distance(WIP_Polygon::HalfEdge edge_a, WIP_Polygon::HalfEdge edge_b, WIP_Polygon::Collider* a, WIP_Polygon::Collider* b, glm::vec3& normal) {
		glm::vec3 pos = edge_a.Direction();
		//still f'ing around with scale issues that pop up in corner collisions.
		glm::vec3 edge_a_dir = a->rotation * edge_a.Direction();
		//edge_a_dir = edge_a.Direction();
		//edge_a_dir = glm::inverse(b->rotation) * a->rotation * edge_a.Direction();
		glm::vec3 edge_a_head = a->m_localToWorld * glm::vec4(edge_a.origin->position, 1.0f);
		//edge_a_head = edge_a.origin->position;
		//edge_a_head = glm::inverse(b->m_localToWorld) * a->m_localToWorld * glm::vec4(edge_a.origin->position, 1.0f);
		glm::vec3 edge_b_dir = b->rotation * edge_b.Direction();
		//std::cout << "b rotation: " << b->rotation.x << "," << b->rotation.y << "," << b->rotation.z << "," << b->rotation.w << "\n";
		//edge_b_dir = glm::inverse(a->rotation) * b->rotation * edge_b.Direction();
		//edge_b_dir = edge_b.Direction();
		glm::vec3 edge_b_head = b->m_localToWorld * glm::vec4(edge_b.origin->position, 1.0f);
		//edge_b_head = glm::inverse(a->m_localToWorld) * b->m_localToWorld * glm::vec4(edge_b.origin->position, 1.0f);
		//edge_b_head = edge_b.origin->position;
		if (glm::dot(glm::abs(edge_a_dir), glm::abs(edge_b_dir)) > PARALLEL) {
			return std::numeric_limits<float>::lowest();
		} 
		normal = glm::normalize(glm::cross(edge_a_dir, edge_b_dir));
		if (glm::dot(normal, edge_a_head - a->center) < 0.0f)
		//if (glm::dot(normal, glm::vec3(a->m_localToWorld * glm::vec4(a->center,1.0f) - b->m_localToWorld * glm::vec4(b->center,1.0f))) < 0.0f)
		{
			normal = -normal;
		}
		//return glm::dot(normal, glm::vec3(glm::scale(glm::mat4(1.0f), b->scale) * glm::vec4(edge_b_head,0.0f)) - glm::vec3(glm::scale(glm::mat4(1.0f), b->scale) * glm::vec4(edge_a_head,0.0f)));
		return glm::dot(normal, edge_b_head - edge_a_head);

	}

	float ClosestPtSegmentSegment(glm::vec3 p1, glm::vec3 q1, glm::vec3 p2, glm::vec3 q2, float& s, float& t, glm::vec3& c1, glm::vec3& c2) {
		//TODO optimize division by e in non-degenerate case
		
		glm::vec3 d1 = q1 - p1;
		glm::vec3 d2 = q2 - p2;
		glm::vec3 r = p1 - p2;
		float a = glm::dot(d1, d1);
		float e = glm::dot(d2, d2);
		float f = glm::dot(d2, r);

		if (a <= EPSILON && e <= EPSILON) {
			s = t = 0.0f;
			c1 = p1;
			c2 = p2;
			return glm::dot(c1 - c2, c1 - c2);
		}

		if (a <= EPSILON) {
			s = 0.0f;
			t = f / e;
			t = glm::clamp(t, 0.0f, 1.0f);
		}
		
		else {
			float c = glm::dot(d1, r);
			if (e <= EPSILON) {
				t = 0.0f;
				s = glm::clamp(-c / a, 0.0f, 1.0f);
			}
			else {
				float b = glm::dot(d1, d2);
				float denom = a * e - b * b;

				if (denom != 0.0f) {
					s = glm::clamp((b * f - c * e) / denom, 0.0f, 1.0f);
				}
				
				else {
					s = 0.0f;
				}

				t = (b * s + f) / e;

				if (t < 0.0f) {
					t = 0.0f;
					s = glm::clamp(-c / a, 0.0f, 1.0f);
				}
				else if (t > 1.0f) {
					t = 1.0f;
					s = glm::clamp((b - c) / a, 0.0f, 1.0f);
				}
			}
		}

		c1 = p1 + d1 * s;
		c2 = p2 + d2 * t;
		return glm::dot(c1 - c2, c1 - c2);
	}

	bool BuildMinkowskiFace(WIP_Polygon::Collider* a, WIP_Polygon::Collider* b, WIP_Polygon::HalfEdge edge_a, WIP_Polygon::HalfEdge edge_b) {
		if (edge_a.incident_face == nullptr || edge_b.incident_face == nullptr) { return false; }
		glm::vec3 norm_a = a->rotation * edge_a.incident_face->normal;
		glm::vec3 norm_b{};
		if (edge_a.twin->incident_face != nullptr) {
			norm_b = a->rotation * edge_a.twin->incident_face->normal;
		}
		else {
			norm_b = -norm_a;
		}
		glm::vec3 norm_c = b->rotation * edge_b.incident_face->normal;
		glm::vec3 norm_d{};
		if (edge_b.twin->incident_face != nullptr) {
			norm_d = b->rotation * edge_b.twin->incident_face->normal;
			//std::cout << "this should never be the case when b is a quad" << "\n";
		}
		else {
			norm_d = -norm_c;
		}
		glm::vec3 ba = a->rotation * (edge_a.next->origin->position - edge_a.origin->position);
		glm::vec3 dc = b->rotation * (edge_b.next->origin->position - edge_b.origin->position);

		bool t = IsMinkowskiFace(norm_a, norm_b, -norm_c, -norm_d, ba, dc);
		return t;
	}

	bool IsMinkowskiFace(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, glm::vec3 ba, glm::vec3 dc) {
	//doesn't work with parallel normals of double sided planes
	//glm::vec3 b_x_a = glm::cross(b, a);
	//glm::vec3 d_x_c = glm::cross(d, c);
	glm::vec3 b_x_a = ba;
	glm::vec3 d_x_c = dc;

	float cba = glm::dot(c, b_x_a);
	float dba = glm::dot(d, b_x_a);
	float adc = glm::dot(a, d_x_c);
	float bdc = glm::dot(b, d_x_c);

	return cba * dba < 0 && adc * bdc < 0 && cba * bdc > 0;
	}

	PlaneQuery QueryFaceDirections(WIP_Polygon::Collider* a, WIP_Polygon::Collider* b) {
		PlaneQuery q{};
		q.max_distance = std::numeric_limits<float>::lowest();
		q.min_penetration = std::numeric_limits<float>::lowest();
		q.max_index = 0;
		q.min_index = 0;
		for (int i = 0; i < a->collider->planes.size(); i++) {
			WIP_Polygon::Plane planeA = a->collider->planes[i];
			//TODO create a rotation and translation matrix without scaling
			glm::vec3 vertex_b = glm::inverse(a->m_localToWorld) * glm::vec4(b->GetSupport(a->rotation * -planeA.normal), 1.0f);
			//need to put scale back in or collision won't be accurate.
			float d = glm::dot(planeA.normal, glm::vec3(glm::scale(glm::mat4(1.0f), a->scale) * glm::vec4(planeA.edge->origin->position, 0.0f)));
			float v = glm::dot(planeA.normal, glm::vec3(glm::scale(glm::mat4(1.0f), a->scale) * glm::vec4(vertex_b, 0.0f)));
			float distance = v - d;
			if (i == 1) {
				//Debug::DrawDebugCube(vert, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(0.1f), Colors::LightPink, 1.0f);
				//Debug::DrawDebugLine(a.center, a.center + (a.rotation * planeA.normal), Colors::LightPink, 1.0f);
				//Debug::DrawDebugCube(plane_origin, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(0.1f), Colors::LightPink, 1.0f);
			}

			if (distance > q.max_distance) {
				q.max_distance = distance;
				q.max_index = i;
			}
			if (distance <= 0.0f && distance > q.min_penetration) {
				q.min_penetration = distance;
				q.min_index = i;
			}
		}
		return q;
	}

	EdgeQuery QueryEdgeDirections(WIP_Polygon::Collider* a, WIP_Polygon::Collider* b) {
		EdgeQuery q{};
		q.max_distance = std::numeric_limits<float>::lowest();
		q.min_distance = std::numeric_limits<float>::lowest();
		q.max_edge_a = 0;
		q.max_edge_b = 0;
		q.min_edge_a = 0;
		q.min_edge_b = 0;
		for (int i_a = 0; i_a < a->collider->edges.size(); i_a++)
		{
			WIP_Polygon::HalfEdge edge_a = a->collider->edges[i_a];
			for (int i_b = 0; i_b < b->collider->edges.size(); i_b++)
			{
				WIP_Polygon::HalfEdge edge_b = b->collider->edges[i_b];
				if (BuildMinkowskiFace(a, b, edge_a, edge_b)) {
					glm::vec3 n{};
					float separation = Distance(edge_a, edge_b, a, b, n);
					if (separation > q.max_distance) {
						q.max_distance = separation;
						q.max_edge_a = i_a;
						q.max_edge_b = i_b;
					}
					if (separation < 0.0f && separation > q.min_distance) 
					{
						q.min_distance = separation;
						q.min_edge_a = i_a;
						q.min_edge_b = i_b;
						q.edge_normal = n;
					}
				}
			}
		}
		return q;
	}

	bool Overlap(WIP_Polygon::Collider* a, WIP_Polygon::Collider* b, WIP_Polygon::ContactManifold& manifold) {
		PlaneQuery q_a = QueryFaceDirections(a, b);
		if (q_a.max_distance > 0.0f) {
			return false;
		}
		PlaneQuery q_b = QueryFaceDirections(b, a);
		if (q_b.max_distance > 0.0f) {
			return false;
		}
		EdgeQuery e = QueryEdgeDirections(a, b);
#define TEST_EDGE
#ifdef TEST_EDGE
//#define DEBUG_1
#ifdef DEBUG_1
		std::cout << "e.max_distance -> " << e.max_distance << "\n";
		Debug::DrawDebugCube(a.m_localToWorld * glm::vec4(a.cube.edges[e.max_edge_a].origin->position, 1.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(0.1f), Colors::BabyBlue, 1.0);
		Debug::DrawDebugCube(a.m_localToWorld * glm::vec4(a.cube.edges[e.max_edge_a].origin->position, 1.0f)
			+ glm::vec4(a.rotation * a.cube.edges[e.max_edge_a].Direction(), 1.0f)
			, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(0.1f), Colors::Beach, 1.0);
		Debug::DrawDebugCube(b.m_localToWorld * glm::vec4(b.cube.edges[e.max_edge_b].origin->position, 1.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(0.1f), Colors::Creamsicle, 1.0);
		Debug::DrawDebugCube(b.m_localToWorld * glm::vec4(b.cube.edges[e.max_edge_b].origin->position, 1.0f)
			+ glm::vec4(b.rotation * b.cube.edges[e.max_edge_b].Direction(), 1.0f)
			, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(0.1f), Colors::Orange, 1.0);
#endif
		if (e.max_distance > 0.0f) {
			std::cout << "edge exit" << "\n";
			return false;
		}
//#define DEBUG

		//CreatePlaneContact(a, b, q_a, q_b, manifold);

		bool blsFaceContactA = q_a.min_penetration > e.min_distance;
		bool blsFaceContactB = q_b.min_penetration > e.min_distance;
		//std::cout << "qa min_pen -> " << q_a.min_penetration << " qb min_pen -> " << q_b.min_penetration << " e min_dist -> " << e.min_distance <<  "\n";
		if (blsFaceContactA || /*&&*/ blsFaceContactB) {
			CreatePlaneContact(a, b, q_a, q_b, manifold);

		}
		else {
			CreateEdgeContact(a, b, e, manifold);
		}
#endif
		return true;
	}

	void CreatePlaneContact(WIP_Polygon::Collider* a, WIP_Polygon::Collider* b, PlaneQuery query_A, PlaneQuery query_B, WIP_Polygon::ContactManifold& manifold) {
		if (query_A.min_penetration > query_B.min_penetration) {
			manifold = ClipPolygon(b, a, query_A);
			manifold.contact_normal = -manifold.contact_normal;
		}
		else{
			manifold = ClipPolygon(a, b, query_B);
		}
#ifdef DEBUG
		//Debug::DrawDebugLine(a->center, a->center + manifold.contact_normal * glm::abs(manifold.contact_penetration), Colors::Green, 1.0f);
#endif

	}

	void CreateEdgeContact(WIP_Polygon::Collider* a, WIP_Polygon::Collider* b, EdgeQuery e, WIP_Polygon::ContactManifold& manifold) {
		manifold.contact_point_count = 1;
		glm::vec3 p1 = a->m_localToWorld * glm::vec4(a->collider->edges[e.min_edge_a].origin->position, 1.0f);
		glm::vec3 q1 = a->m_localToWorld * glm::vec4(a->collider->edges[e.min_edge_a].origin->position + a->collider->edges[e.min_edge_a].Direction(), 1.0f);
		glm::vec3 p2 = b->m_localToWorld * glm::vec4(b->collider->edges[e.min_edge_b].origin->position, 1.0f);
		glm::vec3 q2 = b->m_localToWorld * glm::vec4(b->collider->edges[e.min_edge_b].origin->position + b->collider->edges[e.min_edge_b].Direction(), 1.0f);
		float s{};
		float t{};
		glm::vec3 c1{};
		glm::vec3 c2{};
		float penetration = glm::sqrt(ClosestPtSegmentSegment(p1, q1, p2, q2, s, t, c1, c2));
		manifold.contact_points.push_back((c1 + (c2 - c1) * 0.5f));
		manifold.contact_penetration = e.min_distance;
		//manifold.contact_normal = glm::normalize(c2 - c1);
		manifold.contact_normal = -e.edge_normal;
		manifold.contact_type = "edge";

#ifdef DEBUG
		Debug::DrawDebugCube(c1, IDENTITY_QUAT, glm::vec3(0.1f), Colors::Red, 1.0f);
		Debug::DrawDebugCube(c2, IDENTITY_QUAT, glm::vec3(0.1f), Colors::LightPink, 1.0f);
		Debug::DrawDebugLine(c1, c2, Colors::Strawberry, 1.0f);
		Debug::DrawDebugLine(c1, c1 - e.edge_normal, Colors::Watermelon, 1.0f);

#endif
	}

	WIP_Polygon::Plane* FindIncidentPlane(WIP_Polygon::Collider* incident, WIP_Polygon::Collider* reference, PlaneQuery& plane_query) {
		float min_dot = std::numeric_limits<float>::max();
		float dot{};
		WIP_Polygon::Plane* incident_plane{};
		WIP_Polygon::Plane reference_plane = reference->collider->planes[plane_query.min_index];
		glm::vec3 ref_plane_normal_ws = reference->rotation * reference_plane.normal;
		for (int i = 0; i < incident->collider->planes.size(); i++) {
			dot = glm::dot(ref_plane_normal_ws, incident->rotation * incident->collider->planes[i].normal);
			if (dot < min_dot) {
				min_dot = dot;
				incident_plane = &incident->collider->planes[i];
			}
		}
		return incident_plane;
	}

	std::vector<glm::vec3> IntersectLinePlane(glm::vec3 plane_origin, glm::vec3 plane_normal, glm::vec3 line_start, glm::vec3 line_end, float& factor, std::vector<glm::vec3> in) {
		std::vector<glm::vec3> out = in;
		glm::vec3 l = line_end - line_start;
		float ldotn = glm::dot(l, plane_normal);
		glm::vec3 start_to_origin = plane_origin - line_start;
		float w = glm::dot(start_to_origin, plane_normal);
		//line perpendicular to plane
		if (ldotn == 0.0f) {
			if (w < 0.0f) {
				//both outside plane. keep neither
			}
			else if (w >= 0.0f) {
				//both inside plane. 
				out.push_back(line_end);
			}
			//abort early to prevent division by 0
			return out;
		}
		factor = w / ldotn;
		//start point on plane case
		if (w == 0.0f) {
			//start on plane, end in front of plane
			if (ldotn > 0.0f) {
				//keep neither
			}
			//start on plane, end behind plane
			else if (ldotn < 0.0f) {
				//keep line_end
				out.push_back(line_end);
			}
		}
		//non-intersecting, both points on one side of plane
		if (factor < 0.0f || factor >= 1.0f) {
			//both points in front of plane
			if (w < 0.0f) {
				//keep neither
			}
			//both points behind plane
			else if (w > 0.0f) {
				//keep line end
				out.push_back(line_end);
			}
		}
		//intersecting case
		else if (factor > 0.0f && factor < 1.0f) {
			glm::vec3 intersect = line_start + l * factor;
			//start behind plane, end in front of plane
			if (ldotn > 0.0f) {
				//keep intersection pt
				out.push_back(intersect);
			}
			//start in front of plane, end behind plane
			else if (ldotn < 0.0f) {
				//keep intersection pt, keep line_end
				out.push_back(intersect);
				out.push_back(line_end);
			}
		}
		return out;
	}

	std::vector<glm::vec3> Intersect(glm::vec3 plane_origin, glm::vec3 plane_normal, glm::vec3 line_start, glm::vec3 line_end, std::vector<glm::vec3>in) {
		std::vector<glm::vec3> out = in;
		glm::vec3 l = line_end - line_start;
		float ldotn = glm::dot(l, plane_normal);
		glm::vec3 start_to_origin = plane_origin - line_start;
		float w = glm::dot(start_to_origin, plane_normal);
		float factor = w / ldotn;
		if(factor == 1 && w < 0){}
	}

	int IntersectSegmentPlane(glm::vec3 a, glm::vec3 b, glm::vec3 plane_normal, glm::vec3 plane_point, float& t, glm::vec3& q) {
		glm::vec3 ab = b - a;
		float d = glm::dot(plane_normal, plane_point);
		t = (d - glm::dot(plane_normal, a)) / glm::dot(plane_normal, ab);
		if (t >= 0.0f && t <= 1.0f) {
			q = a + t * ab;
			return 1;
		}
		return 0;
	}

	int ClassifyPointToPlane(glm::vec3 p, glm::vec3 plane_normal, glm::vec3 plane_point) {
		float d = glm::dot(plane_normal, plane_point);
		float dist = glm::dot(plane_normal, p) - d;
		if (dist > PLANE_THICKNESS_EPSILON) {
			return POINT_IN_FRONT_OF_PLANE;
		}
		if (dist < -PLANE_THICKNESS_EPSILON) {
			return POINT_BEHIND_PLANE;
		}
		return POINT_ON_PLANE;
	}

	WIP_Polygon::ContactManifold ClipPolygon(WIP_Polygon::Collider* incident, WIP_Polygon::Collider* reference, PlaneQuery plane_query) {
		//TODO make consistent w/r/t always moving 1 boxcollider (a)
		WIP_Polygon::Plane* incident_plane = FindIncidentPlane(incident, reference, plane_query);
		glm::vec3 incident_plane_normal = incident->rotation * incident_plane->normal;
		WIP_Polygon::Plane reference_plane = reference->collider->planes[plane_query.min_index];
		std::vector<glm::vec3>back_verts{};
		std::vector<glm::vec3>clip_verts{};
		std::vector<glm::vec3> incident_in_ref_space_verts{};

#ifdef DEBUG
		std::vector<glm::vec3> debug_incident_verts_ws{};
		std::vector<glm::vec3> debug_ref_verts_ws{};

		WIP_Polygon::HalfEdge* debug_start_edge = incident_plane->edge;
		WIP_Polygon::HalfEdge* debug_current_edge = debug_start_edge;
		do {
			glm::vec3 v = incident->m_localToWorld * glm::vec4(debug_current_edge->origin->position, 1.0f);
			debug_incident_verts_ws.push_back(v);
			debug_current_edge = debug_current_edge->next;
		} while (debug_current_edge != debug_start_edge);

		debug_start_edge = reference_plane.edge;
		debug_current_edge = debug_start_edge;
		do {
			glm::vec3 v = reference->m_localToWorld * glm::vec4(debug_current_edge->origin->position, 1.0f);
			debug_ref_verts_ws.push_back(v);
			debug_current_edge = debug_current_edge->next;
		} while (debug_current_edge != debug_start_edge);

		CheckPositions(debug_incident_verts_ws, Colors::Orange, 0.05f);
		CheckPositions(debug_ref_verts_ws, Colors::Green, 0.05f);
		float d = glm::dot(reference_plane.edge->origin->position, reference_plane.normal);
		glm::vec3 start_ref = reference->center + reference->rotation * reference_plane.normal * d;
		glm::vec3 end_ref = start_ref + reference->rotation * reference_plane.normal;
		float d_i = glm::dot(incident_plane->edge->origin->position, incident_plane->normal);
		glm::vec3 start_inc = incident->center + incident->rotation * incident_plane->normal * d;
		glm::vec3 end_inc = start_inc + incident->rotation * incident_plane->normal;
		Debug::DrawDebugLine(start_ref,end_ref, Colors::White, 1.0f);
		Debug::DrawDebugLine(start_inc, end_inc, Colors::Red, 1.0f);

#endif

		WIP_Polygon::HalfEdge* start_edge = incident_plane->edge;
		WIP_Polygon::HalfEdge* current_edge = start_edge;
		do {
			glm::vec3 v = glm::inverse(reference->m_localToWorld) * incident->m_localToWorld * glm::vec4(current_edge->origin->position, 1.0f);
			incident_in_ref_space_verts.push_back(v);
			current_edge = current_edge->next;
		} while (current_edge != start_edge);

		start_edge = reference_plane.edge;
		current_edge = start_edge;
		//std::vector<WIP_Polygon::Plane*> clip_planes{};
		std::vector<WIP_Polygon::Plane> clip_planes{};
		do {
			/*at first I thought clipping against side planes meant you clipped against the face planes that were adjacent to the reference plane
			and that were a part of the collision shape.
			but the side planes are actually just planes that are perpendicular to the reference plane and aren't a part of the collision shape. they get
			calculated at runtime.
			*/
			WIP_Polygon::Plane side_plane{};
			side_plane.edge = current_edge;
			side_plane.normal = glm::normalize(glm::cross(current_edge->Direction(), reference_plane.normal));
			//clip_planes.push_back(current_edge->twin->incident_face);
			clip_planes.push_back(side_plane);
			current_edge = current_edge->next;
		} while (current_edge != start_edge);
		int num_planes = clip_planes.size();
		clip_verts = incident_in_ref_space_verts;
//#define DEBUG_2
#ifdef DEBUG_2
		for (int i = 0; i < clip_planes.size(); i++) {
			glm::vec3 start = reference->m_localToWorld * glm::vec4(clip_planes[i].normal * glm::dot(clip_planes[i].normal, clip_planes[i].edge->origin->position), 1.0f);
			glm::vec3 end = start + reference->rotation * clip_planes[i].normal * 0.5f;
			Debug::DrawDebugCube(start, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(0.1f), Colors::Strawberry, 1.0f);
			CheckLines(start, end, Colors::Red);
		}
#endif

#ifdef DEBUG
		//CheckPositions(clip_verts, Colors::Purple, 0.05f);
#define ITERATION 0
#endif

		std::vector<glm::vec3> out_verts{};
		for (int i = 0; i < num_planes; i++) {
			int num_verts = clip_verts.size();
			//WIP_Polygon::Plane& clip_plane = *clip_planes[i];
			WIP_Polygon::Plane& clip_plane = clip_planes[i];
#ifdef DEBUG
			if (i == ITERATION) {
				float dist = glm::dot(clip_plane.edge->origin->position, clip_plane.normal);
				std::cout << dist << "\n";
				glm::vec3 origin = clip_plane.normal * dist;
				glm::vec3 end = origin + clip_plane.normal;
				Debug::DrawDebugCube(end, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(0.1f), Colors::Blue, 1.0f);
				Debug::DrawDebugLine(origin, end, Colors::Blue, 1.0f);
			}
#endif
			//what if num_verts = 0 because all verts are clipped?
			glm::vec3 point_a{};
			int a_side{};
			if (num_verts > 0) {
				point_a = clip_verts[num_verts - 1];
				a_side = ClassifyPointToPlane(point_a, clip_plane.normal, clip_plane.edge->origin->position);
			}
			for (int j = 0; j < num_verts; j++) {
				glm::vec3 point_b = clip_verts[j];
#ifdef DEBUG
				if (i == ITERATION) {
					//Debug::DrawDebugCube(point_a, IDENTITY_QUAT, glm::vec3(0.1f), Colors::Purple, 1.0f);
					//Debug::DrawDebugCube(point_b, IDENTITY_QUAT, glm::vec3(0.1f), Colors::Purple, 1.0f);
					//Debug::DrawDebugLine(point_a, point_b, Colors::Red, 2.0f);
				}

#endif

				int b_side = ClassifyPointToPlane(point_b, clip_plane.normal, clip_plane.edge->origin->position);
				if (b_side == POINT_IN_FRONT_OF_PLANE) {
					if (a_side == POINT_BEHIND_PLANE) {
						glm::vec3 intersection{};
						float t{};
						IntersectSegmentPlane(point_a, point_b, clip_plane.normal, clip_plane.edge->origin->position, t, intersection);
#ifdef DEBUG
						if (i == ITERATION) {
							//std::cout << "intersection " << j << "\n";
							glm::vec3 ab = point_b - point_a;
							float d = glm::dot(clip_plane.normal, clip_plane.edge->origin->position);
							t = (d - glm::dot(clip_plane.normal, point_a)) / glm::dot(clip_plane.normal, ab);
							glm::vec3 q = point_a + t * ab;
							glm::vec3 plane_start = clip_plane.normal * d;
							glm::vec3 line_end = plane_start + clip_plane.normal;
							//std::cout << "1: " << t << " (" << plane_start.x << "," << plane_start.y << "," << plane_start.z << ")" << " , " << "(" << line_end.x << "," << line_end.y << "," << line_end.z << ")" << "\n";
							//Debug::DrawDebugLine(plane_start, line_end, Colors::Red, 1.0f);
							//Debug::DrawDebugLine(point_a, point_b, Colors::Red, 2.0f);
							//Debug::DrawDebugCube(point_a, IDENTITY_QUAT, glm::vec3(0.2f), Colors::Yellow, 1.0f);
							//Debug::DrawDebugCube(point_b, IDENTITY_QUAT, glm::vec3(0.2f), Colors::Orange, 1.0f);
							//Debug::DrawDebugCube(intersection, IDENTITY_QUAT, glm::vec3(0.2f), Colors::White, 1.0f);

						}
#endif
						int test = ClassifyPointToPlane(intersection, clip_plane.normal, clip_plane.edge->origin->position);
						//std::cout << "test: " << test << "\n";
						//assert(test == POINT_ON_PLANE);
						out_verts.push_back(intersection);
					}
				}

				else if (b_side == POINT_BEHIND_PLANE) {
					if (a_side == POINT_IN_FRONT_OF_PLANE) {
						glm::vec3 intersection{};
						float t{};
						IntersectSegmentPlane(point_a, point_b, clip_plane.normal, clip_plane.edge->origin->position, t, intersection);
#ifdef DEBUG
						if (i == ITERATION) {
							//std::cout << "intersection " << j << "\n";
							glm::vec3 ab = point_b - point_a;
							float d = glm::dot(clip_plane.normal, clip_plane.edge->origin->position);
							t = (d - glm::dot(clip_plane.normal, point_a)) / glm::dot(clip_plane.normal, ab);
							glm::vec3 q = point_a + t * ab;
							glm::vec3 plane_start = clip_plane.normal * d;
							glm::vec3 line_end = plane_start + clip_plane.normal;
							//std::cout << "2: " << t << " (" << plane_start.x << "," << plane_start.y << "," << plane_start.z << ")" << " , " << "(" << line_end.x << "," << line_end.y << "," << line_end.z << ")" << "\n";
							//Debug::DrawDebugLine(plane_start, line_end, Colors::Red, 1.0f);
							//Debug::DrawDebugLine(point_a, point_b, Colors::Red, 2.0f);
							//Debug::DrawDebugCube(point_b, IDENTITY_QUAT, glm::vec3(0.2f), Colors::Orange, 1.0f);
							//Debug::DrawDebugCube(point_a, IDENTITY_QUAT, glm::vec3(0.2f), Colors::Yellow, 1.0f);
							//Debug::DrawDebugCube(intersection, IDENTITY_QUAT, glm::vec3(0.2f), Colors::White, 1.0f);
						}
#endif

						out_verts.push_back(intersection);
					}
					else if (a_side == POINT_ON_PLANE) {
						out_verts.push_back(point_a);
					}
					out_verts.push_back(point_b);
				}
				else {
					if (a_side == POINT_BEHIND_PLANE) {
						out_verts.push_back(point_b);
					}
				}
				point_a = point_b;
				a_side = b_side;
			}
			clip_verts = out_verts;
			out_verts.clear();
		}
		std::vector<glm::vec3>contacts{};
		WIP_Polygon::ContactManifold contact_manifold{};
		float min_penetration = std::numeric_limits<float>::max();

		for (int i = 0; i < clip_verts.size(); i++)
		{
			if (ClassifyPointToPlane(clip_verts[i], reference_plane.normal, reference_plane.edge->origin->position) == POINT_BEHIND_PLANE) {
				//transform contact pt to world space
				contacts.push_back(reference->m_localToWorld * glm::vec4(clip_verts[i], 1.0f));
				//need to re-scale the reference and incident verts. otherwise the penetration depth will be wrong when the colliders' scales  != 1.0f.
				//still experimenting with this.
				float d = glm::dot(reference_plane.normal, glm::vec3(glm::scale(glm::mat4(1.0f), reference->scale) * glm::vec4(reference_plane.edge->origin->position, 1.0f)));
				float dist = glm::dot(reference_plane.normal, glm::vec3(glm::scale(glm::mat4(1.0f), reference->scale) * glm::vec4(clip_verts[i], 1.0f))) - d;				
				//float d = glm::dot(reference_plane.normal, reference_plane.edge->origin->position);
				//float dist = glm::dot(reference_plane.normal, clip_verts[i]) - d;

				//std::cout << "dist -> " << dist << "\n";
				if (dist < min_penetration) {
					min_penetration = dist;
					contact_manifold.contact_penetration = dist;

				}
			}
		}
		contact_manifold.contact_point_count = contacts.size();
		contact_manifold.contact_points = contacts;
		contact_manifold.contact_normal = reference->rotation * reference_plane.normal;
		contact_manifold.contact_type = "face";
#ifdef DEBUG
		//std::cout << "check contact_points" << "\n";
		CheckPositions(contact_manifold.contact_points, Colors::Red, 0.12f);
		//std::cout << contact_manifold.contact_points.size() << "\n";
#endif
		return contact_manifold;
	}

	void CheckPositions(std::vector<glm::vec3> v, glm::vec4 col, float size) {
		for (int i = 0; i < v.size(); i++) {
			WIP_Polygon::Debug::DrawDebugCube(v[i], glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(size), col, 1.0f);
		}
	}

	void CheckLines(glm::vec3 origin, glm::vec3 end, glm::vec4 col) {
		WIP_Polygon::Debug::DrawDebugLine(origin, origin + end, col, 1.0f);
	}

	bool IsZeroVector(glm::vec3 v) {
		float length_v = glm::length(v);
		if (length_v <= 0 + EPSILONB) return true;
		return false;
	}

	bool CheckCollision2(float penetration, float& max_penetration, glm::vec3 axis, glm::vec3& contact_axis) {
		//std::cout << "axis " << axis.x << "," << axis.y << "," << axis.z << "\n";
		if (penetration > 0.0f) {
			return false;
		}
		if (penetration > max_penetration) {
				max_penetration = penetration;
				contact_axis = axis;
			}
		return true;		
	}

	void ResolveCollision(WIP_Polygon::BoxCollider a, WIP_Polygon::BoxCollider b, float maxPenetration, glm::vec3 normal) {

		//b face plane origins in world space
		glm::vec3 b_x_s1 = b.center + b.e.x * b.u[0];
		glm::vec3 b_x_s2 = b.center - b.e.x * b.u[0];
		glm::vec3 b_y_s1 = b.center + b.e.y * b.u[1];
		glm::vec3 b_y_s2 = b.center - b.e.y * b.u[1];
		glm::vec3 b_z_s1 = b.center + b.e.z * b.u[2];
		glm::vec3 b_z_s2 = b.center - b.e.z * b.u[2];
	
		std::vector<glm::vec3> out;
		glm::vec3 intersect = glm::vec3(0.0f);
		float factor = 0.0f;

	}

	/*Face FindReferenceFace(BoxCollider reference, glm::vec3 axis, int& reference_face_index) {
		int face_count = reference.faces.size();
		for (int i = 0; i < face_count; i++) {

		}
	}*/

	/*Face FindIncidentFace(BoxCollider incident, BoxCollider reference, int reference_face_index) {
		float min_dot = std::numeric_limits<float>::max();
		float dot;
		Face inc_face{};
		Face reference_face = reference.faces[reference_face_index];
		glm::vec3 ref_face_normal_ws = reference.rotation * reference_face.normal;
		for (int i = 0; i < incident.faces.size(); i++) {
			dot = glm::dot(ref_face_normal_ws, incident.rotation * incident.faces[i].normal);
			if(dot < min_dot){
				min_dot = dot;
				inc_face = incident.faces[i];
			}
		}
		return inc_face;
	}*/

	void AxisInfo(std::string axis) {
		//std::cout << "axis: " << axis << "\n";
	}

	void CollisionDetected(bool detected) {
		if (detected) {
			//std::cout << "collision detected" << "\n";
		}
		else {
			//std::cout << "collision not detected" << "\n";
		}
	}
};
#endif
