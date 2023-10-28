#include "Node.h"
namespace WIP_Polygon {
	Node::Node() :
		center{ glm::vec3(0.0f) }, halfWidth{ 0.5f }, pObjList{nullptr}, level{0}
	{
		pChild.resize(8);
	}
}