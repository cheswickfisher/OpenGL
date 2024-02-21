#ifndef TERRAIN_VOLUME_H
#define TERRAIN_VOLUME_H
#include "Node.h"
#include "MeshRenderer.h"
#include "Rigidbody.h"
#include "AABB.h"
#include "BoxCollider.h"
#include "Textures.h"
#include "Shaders.h"
#include "Debug.h"
#include "Colors.h"
#include "Grid.h"
#include <glm\glm\glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include "stb_image.h"

#include <utility>


namespace WIP_Polygon {
	
	class TerrainVolume : public Grid {
	public:
		static const int num_cubes_xyz = 10;
		char const* path = Textures::perlin_noise_0.second;
		glm::vec3 position;
		float cube_scale_factor;
		float terrain_scale_factor;
		glm::mat4 localToWorld;
		WIP_Polygon::Node* terrain[num_cubes_xyz][num_cubes_xyz][num_cubes_xyz];
		TerrainVolume();
		TerrainVolume(glm::vec3 _position, float _cube_scale_factor);
		void loadTerrain(char const* path);
		int remap(float a0, float a1, float b0, float b1);
		void renderTerrain();
		void renderGrid();
		void insertObject(AABB* _pObject);
		void removeObject(AABB* _pObject);
		glm::vec3 GetClosestGridCellCenterPosition(glm::vec3 local_pos, int& x, int& y, int& z);
		void GetTerrainIndices(glm::vec3 local_pos, int& x, int& y, int& z);
		glm::vec3 GetGridCellCenterPositionFromTerrainIndices(int x, int y, int z);
		std::vector<Rigidbody*> GetCollisionCells(AABB* a, std::vector < std::pair<WIP_Polygon::AABB*, WIP_Polygon::AABB*>>& collision_pairs);

		void BuildGrid() override;
		void RenderGridMeshes() override;
		void InsertObject(AABB* _pObject) override;
		void RemoveObject(AABB* _pObject) override;
		void GetCollisionPairs(AABB* a, std::vector < std::pair<WIP_Polygon::AABB*, WIP_Polygon::AABB*>>& collision_pairs) override;
		void RenderGridLines() override;
	};
}
#endif
