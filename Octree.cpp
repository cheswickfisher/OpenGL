#include "Octree.h"

namespace WIP_Polygon {
	std::vector<glm::vec4> Octree::color_index = {
			Colors::Blue,
			Colors::Purple,
			Colors::Red,
			Colors::Orange,
			Colors::Yellow,
			Colors::Green,
		};
	const int Octree::max_levels = 10;
	Octree::Octree(glm::vec3 _center, float _halfWidth, int _levels) :
		levels{ _levels }, center{ _center }, halfWidth{ _halfWidth }, root{ nullptr } //root{ BuildOctree(_center, _halfWidth, _levels) }
	{}
	Node* Octree::BuildOctree(glm::vec3 _center, float _halfWidth, int _stopDepth) {
		if (_stopDepth < 0) { return nullptr; }
		else {
			Node* pNode = new Node;
			pNode->center = _center;
			pNode->halfWidth = _halfWidth;
			pNode->pObjList = nullptr;
			pNode->level = _stopDepth; 
			glm::vec3 offset;
			float step = _halfWidth * 0.5f;
			for (int i = 0; i < 8; i++) {
				offset.x = ((i & 1) ? step : -step);
				offset.y = ((i & 2) ? step : -step);
				offset.z = ((i & 4) ? step : -step);
				pNode->pChild[i] = BuildOctree(_center + offset, step, _stopDepth - 1);
			}
			return pNode;
		}
	}
	void Octree::InsertObject(Node* _pTree, AABB* _pObject) {
		int index = 0, straddle = 0;
		for (int i = 0; i < 3; i++) {			
			float delta = _pObject->center[i] - _pTree->center[i];
			if (glm::abs(delta) <= _pObject->radius.x) {
				straddle = 1;
				break;
			}
			if (delta > 0.0f) index |= (1 << i);
		}
		if (!straddle && _pTree->pChild[index]) {
			InsertObject(_pTree->pChild[index], _pObject);
		}
		else {
			_pObject->pNextObject = _pTree->pObjList;
			_pTree->pObjList = _pObject;
			_pObject->pCurrentNode = _pTree;
		}
	}
	void Octree::RemoveObject(Node* _pTree, AABB* _pObject) {
		if (_pTree->pObjList != nullptr) {
			if (_pTree->pObjList == _pObject) {
				_pTree->pObjList = _pObject->pNextObject;
				return;
			}
			WIP_Polygon::AABB* pA{ nullptr };
			for (pA = _pTree->pObjList; pA; pA = pA->pNextObject) {
				/*if (_pTree->pObjList->pNextObject == _pObject) {
					_pTree->pObjList->pNextObject = _pObject->pNextObject;
					return;
				}*/
				if (pA->pNextObject == _pObject) {
					pA->pNextObject = _pObject->pNextObject;
					return;
				}
			}
		}
		for (int i = 0; i < _pTree->pChild.size(); i++) {
			if (_pTree->pChild[i]) {
				Octree::RemoveObject(_pTree->pChild[i], _pObject);
			}
		}
		
		/*if (_pTree->pObjList != nullptr) {

			if (_pTree->pObjList == _pObject) {
				_pTree->pObjList = _pObject->pNextObject;
				return;
			}
			else if (_pTree->pObjList->pNextObject == _pObject) {
				_pTree->pObjList->pNextObject = _pObject->pNextObject;
				return;
			}
		}
		for (int i = 0; i < _pTree->pChild.size(); i++) {
			if (!_pTree->pChild[i]) {
				continue;
			}
			Octree::RemoveObject(_pTree->pChild[i], _pObject);
		}*/
	}

	void Octree::GetCollisionPairs(Node* _pTree, std::vector<std::pair <AABB*, AABB*>>& collision_pairs) {
		const int MAX_DEPTH = 40;
		static WIP_Polygon::Node* ancestorStack[MAX_DEPTH];
		static int depth = 0;
		ancestorStack[depth++] = _pTree;
		for (int n = 0; n < depth; n++) {
			WIP_Polygon::AABB* pA{ nullptr };
			WIP_Polygon::AABB* pB{ nullptr };
			for (pA = ancestorStack[n]->pObjList; pA; pA = pA->pNextObject) {
				for (pB = _pTree->pObjList; pB; pB = pB->pNextObject) {
					if (pA == pB) break;//continue flips the testing order
					if (pA->rigidbody->is_static && pB->rigidbody->is_static) { continue; }
					collision_pairs.push_back(std::pair<WIP_Polygon::AABB*, WIP_Polygon::AABB*>(pA, pB));
				}
			}
		}
		for (int i = 0; i < _pTree->pChild.size(); i++) {
			if (_pTree->pChild[i]) {
				GetCollisionPairs(_pTree->pChild[i], collision_pairs);
			}
		}
		depth--;
	}

	void Octree::DrawOctreeGridLines(Node* _octree, int _levels, int _current_level) {
		if (_octree == nullptr) { return; }
		//Debug::DrawDebugCube(_octree->center, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(_octree->halfWidth * 2.0f - static_cast<float>(_current_level * 0.005f)), color_index[_current_level % color_index.size()], glm::mix(0.01f, 5.0f, static_cast<float>(_levels - _current_level) / static_cast<float>(_levels)));
		Debug::DrawDebugCube(_octree->center, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(_octree->halfWidth * 2.0f), Colors::Yellow, 1.0f);
		_current_level = _current_level + 1;
		for (int i = 0; i < _octree->pChild.size(); i++) {
			DrawOctreeGridLines(_octree->pChild[i], _levels, _current_level);
		}
	}

	void Octree::RenderOctreeMeshes(Node* _pTree) {
		if (_pTree->pObjList != nullptr) {
			WIP_Polygon::AABB* pA{ nullptr };

			for (pA = _pTree->pObjList; pA; pA = pA->pNextObject) {
				if(pA->rigidbody->mesh_renderer != nullptr){
					pA->rigidbody->mesh_renderer->DrawMesh();
				}
			}
		}
		for (int i = 0; i < _pTree->pChild.size(); i++) {
			if (_pTree->pChild[i]) {
				Octree::RenderOctreeMeshes(_pTree->pChild[i]);
			}
		}
	}

	void Octree::DebugGrid(Node* _pTree) {
		if (_pTree->pObjList != nullptr) {
			WIP_Polygon::AABB* pA{ nullptr };

			for (pA = _pTree->pObjList; pA; pA = pA->pNextObject) {
				if (pA->rigidbody!= nullptr) {
					std::cout << pA->rigidbody->name << " detected at level [" << _pTree->level << "]" << "\n";
				}
			}
		}
		for (int i = 0; i < _pTree->pChild.size(); i++) {
			if (_pTree->pChild[i]) {
				Octree::DebugGrid(_pTree->pChild[i]);
			}
		}

	}

	void Octree::BuildGrid(){
		if (root) { delete(root); }
		root = Octree::BuildOctree(center, halfWidth, levels);
	}
	void Octree::RenderGridMeshes() {
		RenderOctreeMeshes(root);
	}
	void Octree::InsertObject(AABB* _pObject) {
		RemoveObject(_pObject);
		InsertObject(root, _pObject);
	}
	void Octree::RemoveObject(AABB* _pObject) {
		RemoveObject(root, _pObject);
	}
	
	void Octree::GetCollisionPairs(std::vector < std::pair<WIP_Polygon::AABB*, WIP_Polygon::AABB*>>& collision_pairs) {
		collision_pairs.clear();
		GetCollisionPairs(root, collision_pairs);
	}

	void Octree::RenderGridLines() {
		DrawOctreeGridLines(root, levels, 0);
	}

}