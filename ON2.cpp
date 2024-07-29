#include "ON2.h"

namespace WIP_Polygon {
	ON2::ON2() {
		aabbs = nullptr;
	}
	ON2::ON2(std::vector<WIP_Polygon::AABB*>* _aabbs) {
		aabbs = _aabbs;
	}

	void ON2::BuildGrid() {}
	void ON2::RenderGridMeshes() {}
	void ON2::InsertObject(AABB* _pObject) {}
	void ON2::RemoveObject(AABB* _pObject) {}
	void ON2::GetCollisionPairs(std::vector < std::pair<WIP_Polygon::AABB*, WIP_Polygon::AABB*>>& collision_pairs) 
	{
		aabb_map.clear();
		collision_pairs.clear();
		for (int i = 0; i < aabbs->size(); i++) {
			AABB* pA = aabbs->at(i);
			for (int j = 0; j < aabbs->size(); j++) {
				if (aabbs->at(j) == pA) { continue; }
				AABB* pB = aabbs->at(j);
				AABBKey key{pA, pB};
				AABBMapIter iter = aabb_map.find(key);
				if (iter == aabb_map.end()) {
					aabb_map.insert(AABBKeyPair(key, AABBPair(pA, pB)));
				}
			}
		}
		for (AABBMapIter iter = aabb_map.begin(); iter != aabb_map.end(); iter++) {
			collision_pairs.push_back(std::pair<WIP_Polygon::AABB*, WIP_Polygon::AABB*>(iter->second.box1, iter->second.box2));
		}
	}
	void ON2::RenderGridLines() {}
}