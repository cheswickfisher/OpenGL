#ifndef SCENE_2_H
#define SCENE_2_H
#include "Scene.h"

namespace WIP_Polygon {
	class Scene_2 : public Scene {
		BoxCollider player_collider;
		CharacterControls playerObject;
		AABB player_aabb;
		MeshRenderer player_mr;

		BoxCollider obstacle_collider;
		BoxCollider obstacle_2_collider;
		QuadCollider ground_collider;
		Rigidbody obstacle;
		Rigidbody obstacle_2;
		Rigidbody plane;
		AABB obstacle_aabb;
		AABB obstacle_2_aabb;
		AABB ground_aabb;
		MeshRenderer obstacle_mr;
		MeshRenderer obstacle_2_mr;
		MeshRenderer plane_mr;

		Scene_2();
		void LoadScene() override;
		void DrawScene() override;
		void HandleInput(GLFWwindow* window) override;
	};
}

#endif
