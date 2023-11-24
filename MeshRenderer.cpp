#include "MeshRenderer.h"
#include <glad\glad.h>
#include <glm\glm\glm.hpp>

namespace WIP_Polygon {
	MeshRenderer::MeshRenderer(std::vector<float>* _verts, Shader* _shader, unsigned int* _texture, GameObject* _game_object) :
		game_object{ _game_object},
		verts{ _verts },
		shader{ _shader },
		id{GenerateID()},
		VBO{},
		VAO{},
		texture{_texture}	{
		game_object->mesh_renderer = this;
	}
//must be called after OpenGL context has been created
	void MeshRenderer::SetupMesh() {
		if (game_object == nullptr || verts == nullptr || shader == nullptr || texture == nullptr) { 
			assert("mesh nullptr error");
			return;
		}	
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, verts->size() * sizeof(GLfloat), &(*verts)[0], GL_STATIC_DRAW); //gotta dereference pointer first
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glBindVertexArray(0);
	}
	void MeshRenderer::DrawMesh() {
		shader->use();
		glBindVertexArray(VAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, *texture);
		shader->setMat4("model", game_object->m_localToWorld);
		glDrawArrays(GL_TRIANGLES, 0, verts->size() * .2f);
		glBindVertexArray(0);
	}
}