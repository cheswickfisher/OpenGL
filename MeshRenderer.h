#ifndef MESHRENDERER_H
#define MESHRENDERER_H
#include "GameObject.h"
#include "Textures.h"
#include <vector>
#include "IDGenerator.h"
#include "Shader.h"
#include "RenderShapes.h"
namespace WIP_Polygon {
	class Shader;
	class GameObject;
	class MeshRenderer {
	public:
		GameObject* game_object;
		std::vector<float>* verts;
		Shader* shader;
		unsigned int id;
		unsigned int VBO;
		unsigned int VAO;
		unsigned int* texture;
		MeshRenderer(std::vector<float>* _verts, Shader* _shader, unsigned int* _texture, GameObject* _game_object);
		void SetupMesh();
		void DrawMesh();
	};
}
#endif