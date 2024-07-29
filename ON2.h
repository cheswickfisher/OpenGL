#ifndef ON2_H
#define ON2_H
#include "AABB.h"
#include "Node.h"
#include "Debug.h"
#include "Grid.h"
#include "glm/glm/glm.hpp"
#include <vector>;
#include <map>;


namespace WIP_Polygon {
	struct AABBKey {
		AABB* box1;
		AABB* box2;
		AABBKey(AABB* _box1, AABB* _box2) {
			if (_box1 < _box2) {
				box1 = _box2;
				box2 = _box1;
			}
			else {
				box1 = _box1;
				box2 = _box2;

			}
		}
	};

	struct AABBPair {
		AABB* box1;
		AABB* box2;
		AABBPair(AABB* _a, AABB* _b) {
			if (_a < _b) {
				box1 = _b;
				box2 = _a;
			}
			else {
				box1 = _a;
				box2 = _b;

			}
		}
	};

	inline bool operator < (const AABBKey& a, const AABBKey& b)
	{
		if (a.box1 < b.box1)
			return true;

		if (a.box1 == b.box1 && a.box2 < b.box2)
			return true;

		return false;
	}

	typedef std::pair<AABBKey, AABBPair>AABBKeyPair;
	typedef std::map<AABBKey, AABBPair>AABBMap;
	typedef std::map<AABBKey, AABBPair>::iterator AABBMapIter;

	class ON2 : public Grid{
	public:
		AABBMap aabb_map{};
		std::vector<WIP_Polygon::AABB*>* aabbs;
		void BuildGrid() override;
		void RenderGridMeshes() override;
		void InsertObject(AABB* _pObject) override;
		void RemoveObject(AABB* _pObject) override;
		void GetCollisionPairs(std::vector < std::pair<WIP_Polygon::AABB*, WIP_Polygon::AABB*>>& collision_pairs) override;
		void RenderGridLines() override;
		
		ON2();
		ON2(std::vector<WIP_Polygon::AABB*>* _aabbs);
	};
}
#endif

