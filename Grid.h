#ifndef GRID_H
#define GRID_H
#include "AABB.h"
#include <utility>
#include <vector>

namespace WIP_Polygon {
	class Grid {
	public:
		virtual void BuildGrid() = 0;
		virtual void RenderGridMeshes() = 0;
		virtual void InsertObject(AABB* _pObject) = 0;
		virtual void RemoveObject(AABB* _pObject) = 0;
		virtual void GetCollisionPairs(std::vector < std::pair<WIP_Polygon::AABB*, WIP_Polygon::AABB*>>& collision_pairs) = 0;
		virtual void RenderGridLines() = 0;
	protected:
		Grid();
		virtual ~Grid() = 0;
	};
}

#endif
