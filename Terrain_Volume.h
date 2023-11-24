#ifndef TERRAIN_VOLUME_H
#define TERRAIN_VOLUME_H
#include "MeshRenderer.h"
#include "Rigidbody.h"
#include "BoxCollider.h"
#include "Textures.h"
#include "Shaders.h"
#include <glm\glm\glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include "stb_image.h"

namespace WIP_Polygon {
	static const int cells_per_row = 10;
	class TerrainVolume {
	public:
		glm::vec3 position;
		int terrain_scale;
		glm::mat4 localToWorld;
		WIP_Polygon::Rigidbody terrain [cells_per_row][cells_per_row][cells_per_row];
		TerrainVolume();
		TerrainVolume(glm::vec3 _position, int _scale);
		void loadTerrain(char const* path);
		void load_test();
		void renderTerrain();
	};
}
#endif
