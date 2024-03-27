#ifndef SCENE_1_H
#define SCENE_1_H
#include "Scene.h"

namespace WIP_Polygon {
	class Scene_1 : public Scene {
	public:		
		BoxCollider player_collider;
		CharacterControls playerObject;
		AABB player_aabb;
		MeshRenderer player_mr;

		Scene_1();
		void LoadScene() override;
		void DrawScene() override;
		void HandleInput(GLFWwindow* window) override;

		void InputMethod1(GLFWwindow* window);
		void InputMethod2(GLFWwindow* window);
	};
}
#endif