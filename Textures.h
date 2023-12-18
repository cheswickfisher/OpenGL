#ifndef TEXTURES_H
#define TEXTURES_H
#include "glad\glad.h"
#include "glfw3.h"
#include "stb_image.h"
#include <iostream>
#include <vector>
#include <utility>

namespace WIP_Polygon {
	class Textures {
	public:
		static std::pair<unsigned int, const char*> sandstone_brick_diffuse;
		static std::pair<unsigned int, const char*> pavement_diffuse;
		static std::pair<unsigned int, const char*> rock_cliff_albedo;
		static std::pair<unsigned int, const char*> grid_cell_noise_0;
		static std::pair<unsigned int, const char*> grid_cell_noise_1;
		static std::pair<unsigned int, const char*> perlin_noise_0;
		static std::vector < std::pair<unsigned int, const char*>*> textures;
		static void loadTextures();
		static unsigned int loadTexture(const char* _path);
	};
}
#endif
