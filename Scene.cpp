#include "Scene.h"

namespace WIP_Polygon {
	Scene::Scene() :
		camera{ nullptr },
		debug{ nullptr },
		aabbs{nullptr}, gameobjects{ nullptr }, mesh_renderers{ nullptr },
		//terrain_volume{ nullptr },
		collision_pairs{ nullptr },
		//octree{ nullptr },
		grid {nullptr}
	{}
	Scene::Scene(Camera* _camera, std::vector<WIP_Polygon::AABB*>* _aabbs, std::vector<WIP_Polygon::GameObject*>* _gameobjects,
		std::vector<WIP_Polygon::MeshRenderer*>* _mesh_renderers, std::vector < std::pair<WIP_Polygon::AABB*, WIP_Polygon::AABB*>>* _collision_pairs,
		/*WIP_Polygon::TerrainVolume* _terrain_volume, WIP_Polygon::Octree* _octree,*/ WIP_Polygon::Grid* _grid) :
		camera{_camera}, debug{ new WIP_Polygon::Debug() },
		aabbs{_aabbs}, gameobjects{_gameobjects}, mesh_renderers{_mesh_renderers},
		collision_pairs{_collision_pairs}, /*terrain_volume{_terrain_volume}, octree{_octree},*/ grid{_grid}
	{
	}

	void Scene::PrepCamAndShaderMatrices(glm::vec3 cameraTarget) {
		camera->UpdateRotation();
		camera->UpdatePosition(cameraTarget);
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = camera->ViewMatrix();
		glm::mat4 projection = camera->ProjectionMatrix();//glm::perspective(glm::radians(camera->fov), a, 0.1f, 100.0f);
		WIP_Polygon::Shaders::lightingShader.use();
		WIP_Polygon::Shaders::lightingShader.setMat4("view", view);
		WIP_Polygon::Shaders::lightingShader.setMat4("projection", projection);
	}

	void Scene::DrawMeshes() {
		for (int i = 0; i < mesh_renderers->size(); i++) {
			mesh_renderers->at(i)->game_object->UpdateTransform();
			mesh_renderers->at(i)->DrawMesh();
		}
	}

	void Scene::UpdateAABBS() {
		for (int i = 0; i < aabbs->size(); i++) {
			if (!aabbs->at(i)->rigidbody->is_static) {
				aabbs->at(i)->rigidbody->UpdateTransform();
				aabbs->at(i)->rigidbody->collider->UpdateTransform(aabbs->at(i)->rigidbody->position, aabbs->at(i)->rigidbody->rotation, aabbs->at(i)->rigidbody->collider->scale);
				aabbs->at(i)->center = aabbs->at(i)->rigidbody->position;
				aabbs->at(i)->ConstructFromPointSet(aabbs->at(i)->rigidbody->collider);
				grid->InsertObject(aabbs->at(i));
			}
		}

	}

	Scene::~Scene() {}
}