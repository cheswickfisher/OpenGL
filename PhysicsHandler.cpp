#include "PhysicsHandler.h"

namespace WIP_Polygon {
	PhysicsHandler::PhysicsHandler() {}

	void PhysicsHandler::ApplyForces(std::vector<Rigidbody*>* _rbs) {
		if (_rbs == nullptr) { return; }
		for (int i = 0; i < _rbs->size(); i++) {
			if (_rbs->at(i) == nullptr) { std::cout << "nullptr" << "\n"; continue; }
			_rbs->at(i)->ApplyForces();
		}
	}
	void PhysicsHandler::ClearForces(std::vector<Rigidbody*>* _rbs) {
		if (_rbs == nullptr) { return; }
		for (int i = 0; i < _rbs->size(); i++) {
			if (_rbs->at(i) == nullptr) { continue; }
			_rbs->at(i)->ClearForces();
		}

	}
}