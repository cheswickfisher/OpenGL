#ifndef SCENE_3_H
#define SCENE_3_H
#include "Scene.h"
namespace WIP_Polygon {
	class Scene_3 : public Scene {
	public:
		BoxCollider player_collider;
		QuadCollider ground_collider;
		BoxCollider test_cube_collider;
		CharacterControls playerObject;
		Rigidbody ground_rb;
		Rigidbody test_cube_rb;
		AABB player_aabb;
		AABB ground_aabb;
		AABB test_cube_aabb;
		MeshRenderer player_mr;
		MeshRenderer ground_mr;
		MeshRenderer test_cube_mr;

		Scene_3();
		void LoadScene() override;
		void DrawScene() override;
		void HandleInput(GLFWwindow* window) override;

		void InputMethod1(GLFWwindow* window);


	};
}

#endif
