#include "Shaders.h"
namespace WIP_Polygon {
	Shader Shaders::directional_shader{ "C:/OPENGL/shaders/Vertex.vs", "C:/OPENGL/shaders/Lighting.fs" };
	Shader Shaders::lightingShader{ "C:/OPENGL/shaders/depth_testing.vs", "C:/OPENGL/shaders/depth_testing.fs" };
	Shader Shaders::debugShader{ "C:/OPENGL/shaders/debug_lines.vs", "C:/OPENGL/shaders/debug_lines.fs" };
	std::vector<Shader*>Shaders::shaders = {
		&Shaders::directional_shader,
		&Shaders::lightingShader,
		&Shaders::debugShader
	};
	void Shaders::loadShaders() {
		for (int i = 0; i < shaders.size(); i++) {
			shaders[i]->InitializeShader();
		}
		WIP_Polygon::Shaders::directional_shader.use();
		WIP_Polygon::Shaders::directional_shader.setVec3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));
		WIP_Polygon::Shaders::directional_shader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		WIP_Polygon::Shaders::directional_shader.setVec3("lightPos", glm::vec3(10.0f, 10.0f, 10.0f));
	}
}