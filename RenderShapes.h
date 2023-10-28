#ifndef RENDERSHAPES_H
#define RENDERSHAPES_H
#include <vector>
#include <glm\glm\glm.hpp>
namespace WIP_Polygon {
	class RenderShapes {
	public:
		static std::vector<float>cube;
		static std::vector<float>plane;
		static std::vector<float>circle;

		static std::vector<float> CreateCircle(int _num_verts);
		
	};
}
#endif
