#ifndef SCENE_H
#define SCENE_H

#include <glad\glad.h>
#include <glfw3.h>

#include "Materials.h"
#include "Shaders.h"
#include "Camera.h"
#include "Model.h"
#include "CharacterControls.h"
#include "Rigidbody.h"
#include "CollisionHandler.h"
#include "Debug.h"
#include "Cube.h"
#include "HalfEdge.h"
#include "Manifold.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "QuadCollider.h"
#include "Textures.h"
#include "Colors.h"
#include "MeshRenderer.h"
#include "RenderShapes.h"
#include "Octree.h"
#include "Node.h"
#include "Terrain_Volume.h"
#include "AABB.h"
#include "Preferences.h"
#include "Grid.h"

#include <glfw3.h>
#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>
#include <glm\glm\gtc\quaternion.hpp>
#include <glm\glm\gtx\quaternion.hpp>

#include <iostream>
#include <string>
#include <utility>

namespace WIP_Polygon {
	class Scene {
		public:
			const float infinity = std::numeric_limits<float>::infinity();
			Camera* camera;
			WIP_Polygon::Debug* debug;

			std::vector<WIP_Polygon::AABB*>*aabbs;
			std::vector<WIP_Polygon::GameObject*>*gameobjects;
			std::vector<WIP_Polygon::MeshRenderer*>*mesh_renderers;
			std::vector < std::pair<WIP_Polygon::AABB*, WIP_Polygon::AABB*>>* collision_pairs;
			//WIP_Polygon::TerrainVolume* terrain_volume;
			WIP_Polygon::Octree* octree;
			WIP_Polygon::Grid* grid;

			//this can probably not be virtual
			virtual void LoadScene() = 0;
			virtual void DrawScene() = 0;
			void PrepCamAndShaderMatrices(glm::vec3 cameraTarget);
			void DrawMeshes();
			virtual void HandleInput(GLFWwindow* window) = 0;
			//dunno if i'm gonna end up using this or not.
			virtual void UpdateCamera() = 0;
			virtual ~Scene() = 0;
	protected:
			Scene();
			Scene(Camera* _camera, std::vector<WIP_Polygon::AABB*>* _aabbs, std::vector<WIP_Polygon::GameObject*>* _gameobjects,
				std::vector<WIP_Polygon::MeshRenderer*>* _mesh_renderers, std::vector < std::pair<WIP_Polygon::AABB*, WIP_Polygon::AABB*>>* _collision_pairs,
				WIP_Polygon::TerrainVolume* _terrain_volume, WIP_Polygon::Octree* _octree, WIP_Polygon::Grid*);
	};
}
#endif
