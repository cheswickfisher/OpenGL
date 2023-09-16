#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <array>
#include <vector>
#include <string>
#include <glm/glm/glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include "AABB.h"
#include "Face.h"
#include "Cube.h"
#include "Collider.h"

namespace WIP_Polygon {
	class BoxCollider : public Collider {
	public:
		/*glm::vec3 center;
		std::array<glm::vec3, 3> u;
		glm::vec3 e;
		glm::quat rotation;
		glm::vec3 scale;
		glm::mat4 m_localToWorld;
		AABB aabb;*/
		//std::array<Face, 6> faces;
		/*std::vector<glm::vec3> verts = {
			glm::vec3(-0.5f,0.5f,0.5f), glm::vec3(0.5f,0.5f,0.5f),
			glm::vec3(0.5f,0.5f,-0.5f), glm::vec3(-0.5f,0.5f,-0.5f),
			glm::vec3(-0.5f,-0.5f,0.5f), glm::vec3(0.5f,-0.5f,0.5f),
			glm::vec3(0.5f,-0.5f,-0.5f), glm::vec3(-0.5f,-0.5f,-0.5f)};*/
			/*std::array<int, 4> left_verts = { 1,5,6,2 };
			std::array<int, 4> right_verts = { 0,3,7,4 };
			std::array<int, 4> forward_verts = { 1,0,4,5 };
			std::array<int, 4> backward_verts = { 2,6,7,3 };
			std::array<int, 4> up_verts = { 1,2,3,0 };
			std::array<int, 4> down_verts = { 5,4,7,6 };*/
		WIP_Polygon::Cube cube{};
		BoxCollider() /*:
			aabb{ AABB() },
			cube{ WIP_Polygon::Cube() }*/
			:
			Collider{glm::vec3(1.0f), glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
			cube{WIP_Polygon::Cube()}
		{
			collider = &cube;
			name = "box";
			/*center = glm::vec3(0.0f);
			u = { glm::vec3(1.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f) };
			e = glm::vec3(0.5f);
			rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
			scale = glm::vec3(1.0f);
			glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 rot_combined = rotX * rotY * rotZ;
			m_localToWorld = glm::translate(glm::mat4(1.0f), center) * rot_combined * glm::scale(glm::mat4(1.0f), scale);*/
			/*Face right = Face(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{2, 3, 4, 5}, right_verts);
			Face left = Face(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{2, 3, 4, 5}, left_verts);
			Face forward = Face(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{0, 1, 4, 5}, forward_verts);
			Face backward = Face(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{0, 1, 4, 5}, backward_verts);
			Face up = Face(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{0, 1, 2, 3}, up_verts);
			Face down = Face(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{0, 1, 2, 3}, down_verts);
			faces = { right, left, forward, backward, up, down};*/
		}

		BoxCollider(glm::vec3 _scale) /*:
			aabb{AABB{glm::distance(glm::vec3(0.0f), _scale), glm::vec3(0.0f)}},
			cube{ WIP_Polygon::Cube() }*/
			:
			Collider{ _scale, glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 0.0f) },
			cube{ WIP_Polygon::Cube() }
		{
			collider = &cube;
			name = "box";

			/*center = glm::vec3(0.0f);
			u = { glm::vec3(1.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f) };
			e = _scale * 0.5f;
			rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
			scale = glm::vec3(_scale.x, _scale.y, _scale.z);
			glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 rot_combined = rotX * rotY * rotZ;
			m_localToWorld = glm::translate(glm::mat4(1.0f), center) * rot_combined * glm::scale(glm::mat4(1.0f), scale);*/
			/*Face right = Face(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{2, 3, 4, 5}, right_verts);
			Face left = Face(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{2, 3, 4, 5}, left_verts);
			Face forward = Face(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{0, 1, 4, 5}, forward_verts);
			Face backward = Face(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{0, 1, 4, 5}, backward_verts);
			Face up = Face(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{0, 1, 2, 3}, up_verts);
			Face down = Face(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{0, 1, 2, 3}, down_verts);
			faces = { right, left, forward, backward, up, down };*/
		}

		BoxCollider(glm::vec3 _scale, glm::vec3 _position) /*:
			aabb{ AABB{ glm::distance(glm::vec3(0.0f), _scale), _position } },
			cube{ WIP_Polygon::Cube() }*/
			:
			Collider{ _scale, _position,glm::vec3(0.0f, 0.0f, 0.0f) },
			cube{ WIP_Polygon::Cube() }
		{
			collider = &cube;
			name = "box";

			/*center = _position;
			u = { glm::vec3(1.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f) };
			e = _scale * 0.5f;
			rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
			scale = glm::vec3(_scale.x, _scale.y, _scale.z);
			glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 rot_combined = rotX * rotY * rotZ;
			m_localToWorld = glm::translate(glm::mat4(1.0f), center) * rot_combined * glm::scale(glm::mat4(1.0f), scale);*/
			/*Face right = Face(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{2, 3, 4, 5}, right_verts);
			Face left = Face(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{2, 3, 4, 5}, left_verts);
			Face forward = Face(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{0, 1, 4, 5}, forward_verts);
			Face backward = Face(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{0, 1, 4, 5}, backward_verts);
			Face up = Face(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{0, 1, 2, 3}, up_verts);
			Face down = Face(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{0, 1, 2, 3}, down_verts);
			faces = { right, left, forward, backward, up, down };*/
		}

		BoxCollider(glm::vec3 _scale, glm::vec3 _position, glm::vec3 _rotation) /*:
			aabb{ AABB{ glm::distance(glm::vec3(0.0f), _scale), _position } },
			cube{ WIP_Polygon::Cube() }*/
			:
			Collider{ _scale, _position, _rotation },
			cube{ WIP_Polygon::Cube() }
		{
			collider = &cube;
			name = "box";

			/*center = _position;
			glm::quat qPitch = glm::angleAxis(_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			glm::quat qYaw = glm::angleAxis(_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			glm::quat qRoll = glm::angleAxis(_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
			rotation = glm::normalize(qPitch * qYaw * qRoll);
			u = { glm::normalize(rotation * glm::vec3(1.0f,0.0f,0.0f)), glm::normalize(rotation * glm::vec3(0.0f,1.0f,0.0f)), glm::normalize(rotation * glm::vec3(0.0f,0.0f,1.0f)) };
			e = _scale * 0.5f;
			scale = glm::vec3(_scale.x, _scale.y, _scale.z);
			glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 rot_combined = rotX * rotY * rotZ;
			m_localToWorld = glm::translate(glm::mat4(1.0f), center) * rot_combined * glm::scale(glm::mat4(1.0f), scale);*/
			/*Face right = Face(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{2, 3, 4, 5}, right_verts);
			Face left = Face(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{2, 3, 4, 5}, left_verts);
			Face forward = Face(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{0, 1, 4, 5}, forward_verts);
			Face backward = Face(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{0, 1, 4, 5}, backward_verts);
			Face up = Face(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{0, 1, 2, 3}, up_verts);
			Face down = Face(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(e.x, e.y, e.z), std::array<int, 4>{0, 1, 2, 3}, down_verts);
			faces = { right, left, forward, backward, up, down };*/
		}

		void DrawAxes() override {
			glm::vec3 f = rotation * glm::vec3(0.0f, 0.0f, 1.0f) * scale.z * 0.5f;
			glm::vec3 r = rotation * glm::vec3(1.0f, 0.0f, 0.0f) * scale.x * 0.5f;
			glm::vec3 u = rotation * glm::vec3(0.0f, 1.0f, 0.0f) * scale.y * 0.5f;

			Debug::DrawDebugLine(center + f, center + f  + f * 0.5f, Colors::Cyan, 1.0f);
			Debug::DrawDebugLine(center + r, center + r + r * 0.5f, Colors::Red, 1.0f);
			Debug::DrawDebugLine(center + u, center + u + u * 0.5f, Colors::Green, 1.0f);

		}

	};
}
#endif