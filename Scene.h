#ifndef SCENE_H
#define SCENE_H

#include "BoxCollider.h"
#include "QuadCollider.h"
#include "CharacterControls.h"
#include "Rigidbody.h"
#include "AABB.h"
#include "MeshRenderer.h"
#include <vector>

//TODO finish scene implementation after getting voxel terrain set up
namespace WIP_Polygon {
	class Scene {
		WIP_Polygon::CharacterControls playerObject;
		std::vector<Rigidbody> rbs;
		std::vector<AABB> aabbs;
		WIP_Polygon::MeshRenderer mesh_renders;
	};
}

#endif
