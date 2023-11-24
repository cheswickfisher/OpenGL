#include "Shaders.h"
namespace WIP_Polygon {
	Shader Shaders::lightingShader{ "C:/OPENGL/shaders/depth_testing.vs", "C:/OPENGL/shaders/depth_testing.fs" };
	Shader Shaders::debugShader{ "C:/OPENGL/shaders/debug_lines.vs", "C:/OPENGL/shaders/debug_lines.fs" };
	std::vector<Shader*>Shaders::shaders = {
		&Shaders::lightingShader,
		&Shaders::debugShader
	};
	void Shaders::loadShaders() {
		for (int i = 0; i < shaders.size(); i++) {
			shaders[i]->InitializeShader();
		}
	}
}