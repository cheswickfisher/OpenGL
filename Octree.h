#pragma once
#ifndef OCTREE_H
#define OCTREE_H
#include "AABB.h"
#include "Node.h"
#include "Debug.h"
#include "Grid.h"
#include "glm/glm/glm.hpp"

namespace WIP_Polygon {
	class Octree : public Grid {
	private: 
		static std::vector<glm::vec4>color_index;
		static const int max_levels;
	public:
		Node* root;
		int levels;
		glm::vec3 center;
		float halfWidth;
		void DrawOctreeGridLines(Node* _octree, int _level, int _current_level);
		Node* BuildOctree(glm::vec3 _center, float _halfWidth, int _stopDepth);
		void InsertObject(Node* _pTree, AABB* _pObject);
		void RemoveObject(Node* _pTree, AABB* _pObject);
		void GetCollisionPairs(Node* _pTree, std::vector<std::pair <AABB*, AABB*>>& _aabb_pairs);
		void RenderOctreeMeshes(Node* _pTree);
		void DebugGrid(Node* _pTree);

		void BuildGrid() override;
		void RenderGridMeshes() override;
		void InsertObject(AABB* _pObject) override;
		void RemoveObject(AABB* _pObject) override;
		void GetCollisionPairs(std::vector < std::pair<WIP_Polygon::AABB*, WIP_Polygon::AABB*>>& collision_pairs) override;
		void RenderGridLines() override;


		Octree(glm::vec3 _center, float _halfWidth, int _levels);
	};
}

#endif