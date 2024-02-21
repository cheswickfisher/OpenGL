#pragma once
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

namespace WIP_Polygon {

	bool Intersect(WIP_Polygon::AABB a, WIP_Polygon::AABB b) {
		/*return
			a.minX <= b.maxX &&
			a.maxX >= b.minX &&
			a.minY <= b.maxY &&
			a.maxY >= b.minY &&
			a.minZ <= b.maxZ &&
			a.maxZ >= b.minZ;*/
	}
}

glm::vec3 SeparatingAxis(WIP_Polygon::AABB a, WIP_Polygon::AABB b) {
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
		if (yOverlap < minOverlap) { minOverlap = yOverlap; contactNormal = yAxis; }
	}
	else { return glm::vec3(0.0f); }
	if (aminz <= bmaxz &&
		amaxz >= bminz) {
		zOverlap = std::min(std::abs(amaxz - bminz), std::abs(aminz - bmaxz));
		std::cout << "zOverlap :" << zOverlap << "\n";
		if (zOverlap < minOverlap) { minOverlap = zOverlap; contactNormal = zAxis; }
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
			AbsR[i][j] = glm::abs(R[i][j]) /*+ EPSILON*/; //add epsilon constant in header
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


