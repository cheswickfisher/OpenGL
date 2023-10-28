#pragma once
#ifndef OCTREE_H
#define OCTREE_H
#include "AABB.h"
#include "Node.h"
#include "Debug.h"
#include "glm/glm/glm.hpp"

namespace WIP_Polygon {
	class Octree {
	private: 
		static std::vector<glm::vec4>color_index;
		static const int max_levels;
	public:
		Node* root;
		int levels;
		void DrawOctree(Node* _octree, int _level, int _current_level);
		Node* BuildOctree(glm::vec3 _center, float _halfWidth, int _stopDepth);
		void InsertObject(Node* _pTree, AABB* _pObject);
		void RemoveObject(Node* _pTree, AABB* _pObject);
		Octree(glm::vec3 _center, float _halfWidth, int _levels);
	};
}

#endif