#ifndef SHADERS_H
#define SHADERS_H
#include "Shader.h"
#include <vector>
namespace WIP_Polygon {
	class Shaders{
	public:
		static Shader lightingShader;
		static Shader debugShader;
		static std::vector<Shader*>shaders;
		static void loadShaders();
	};
}

#endif
