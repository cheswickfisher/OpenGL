#ifndef UTILITYMETHODS_H
#define UTILITYMETHODS_H
#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>
#include <glm\glm\gtc\quaternion.hpp>
#include <glm\glm\gtx\quaternion.hpp>
#include <vector>
namespace WIP_Polygon {
	static void ExtremePointsAlongDirection(glm::vec3 dir, std::vector<float> points, glm::vec3* min_pt, glm::vec3* max_pt) {
		/*float minproj = std::numeric_limits<float>::max();
		float maxproj = std::numeric_limits<float>::min();
		for (int i = 0; i < points.size(); i++) {
			//only need rotation and scale for transformation
			glm::vec3 pos = glm::vec3(a->m_localToWorld * glm::vec4(points[i].position, 0.0f));
			float proj = glm::dot(pos, dir);
			if (proj < minproj) {
				minproj = proj;
				*min_pt = pos;
			}
			if (proj > maxproj) {
				maxproj = proj;
				*max_pt = pos;
			}
		}*/
	}
	static void ConstructFromPointSet(std::vector<float> _verts, glm::vec3& _scale) {
		float x{};
		float y{};
		float z{};

		glm::vec3 max_pt{};
		glm::vec3 min_pt{};

		glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

		ExtremePointsAlongDirection(right, _verts, &min_pt, &max_pt);
		x = max_pt.x - min_pt.x;
		ExtremePointsAlongDirection(up, _verts, &min_pt, &max_pt);
		y = max_pt.y - min_pt.y;
		ExtremePointsAlongDirection(forward, _verts, &min_pt, &max_pt);
		z = max_pt.z - min_pt.z;

		_scale = glm::vec3(glm::abs(x) * 0.5f, glm::abs(y) * 0.5f, glm::abs(z) * 0.5f);
	}


	static void ConstructBasisFromForward(glm::vec3 _f, glm::vec3& _r, glm::vec3& _u) {
		_r = glm::normalize(glm::cross(_f, glm::vec3(0, 1, 0)));
		_u = glm::normalize(glm::cross(_r, _f));
	}
}

#endif
