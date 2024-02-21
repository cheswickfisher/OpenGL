#include <glad\glad.h>
#include <glfw3.h>

#include "Materials.h"
#include "Shaders.h"
#include "Camera.h"
#include "Model.h"
#include "CharacterControls.h"
#include "Rigidbody.h"
#include "CollisionHandler.h"
#include "Debug.h"
#include "Cube.h"
#include "HalfEdge.h"
#include "Manifold.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "QuadCollider.h"
#include "Textures.h"
#include "Colors.h"
#include "MeshRenderer.h"
#include "RenderShapes.h"
#include "Octree.h"
#include "Node.h"
#include "Terrain_Volume.h"
#include "AABB.h"
#include "Scenes\Scene_1.h"
#include "Preferences.h"

#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>
#include <glm\glm\gtc\quaternion.hpp>
#include <glm\glm\gtx\quaternion.hpp>

#include <iostream>
#include <string>
#include <utility>

#define IDENTITY_QUAT glm::quat(1.0f,0.0f,0.0f,0.0f)

void Octree_Update();
void Octree_Build(WIP_Polygon::Octree*& _octree, std::vector<WIP_Polygon::AABB*>_aabbs);
void Octree_TestAllCollisions(WIP_Polygon::Node* _pTree, std::vector<std::pair <WIP_Polygon::AABB*, WIP_Polygon::AABB*>>& _aabb_pairs);
void update();
void updatePhysics();
void render();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
void updateCameraTransform();


/*const float SCREEN_WIDTH = 1360.0f;
const float SCREEN_HEIGHT = 768.0f;
float a = SCREEN_WIDTH / SCREEN_HEIGHT;*/
const float infinity = std::numeric_limits<float>::infinity();

float lastX = 960.0f;
float lastY = 540.0f;
//float deltaTime = 0.0f;
float lastFrame = 0.0f;

Materials materials;
//WIP_Polygon::Debug debug;
GLFWwindow* window;


/*std::vector < std::pair<WIP_Polygon::AABB*, WIP_Polygon::AABB*>> collision_pairs{};
WIP_Polygon::Octree* octree;
glm::vec3 dirLightDirection(-0.2f, -1.0f, -0.3f);
glm::vec3 dirLightColor(1.0f, 1.0f, 1.0f);*/
WIP_Polygon::CollisionHandler collisionHandler;

WIP_Polygon::Scene_1 scene_1{};

//TODO: make this work (need some way to get playerObject in scene)
WIP_Polygon::Scene& scene{ scene_1 };

//WIP_Polygon::Scene_1 scene{};

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGLAdvanced", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << '\n';
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << '\n';
        return -1;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glEnable(GL_DEPTH_TEST);

    WIP_Polygon::Shaders::loadShaders();
    WIP_Polygon::Textures::loadTextures();
    scene.LoadScene();

    //Octree_Build(octree, aabbs);

    float accumulator = 0;
    float frame_start = static_cast<float>(glfwGetTime());

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        accumulator += deltaTime;
        lastFrame = currentFrame;

        if (accumulator > 0.2f) {
            accumulator = 0.2f;
        }

        scene.HandleInput(window);

        update();

        while (accumulator > fixed_dt) {
            updatePhysics();
            accumulator -= fixed_dt;
        }
        render();
    }

    for (int i = 0; i < scene.mesh_renderers->size(); i++) {
        //glDeleteVertexArrays(1, &(*mesh_renderers[i]).VAO);
        glDeleteVertexArrays(1, &(scene.mesh_renderers->at(i)->VAO));
        glDeleteBuffers(1, &(scene.mesh_renderers->at(i)->VBO));
    }
    glfwTerminate();
	return 0;
}

void update() {
    //update gameobjects that don't have aabbs/collision
    for (int i = 0; i < scene.gameobjects->size(); i++) {
        if (!(scene.gameobjects->at(i)->is_static)) {
            scene.gameobjects->at(i)->UpdateTransform();
        }
    }
}

void updatePhysics() {
    collisionHandler.UpdateSceneDynamicColliders(scene);
    /*Octree_Update();
    std::vector<std::pair <WIP_Polygon::AABB*, WIP_Polygon::AABB*>> aabb_pairs{};
    Octree_TestAllCollisions(octree->root, aabb_pairs);
    ResolveCollisions(aabb_pairs);*/
}

void render() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene.DrawScene();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

/*void Octree_Update() {
    //update dynamic objects nodes in octree
    //TODO: collect dynamic objects in vector and loop through to update
    scene.player_aabb.rigidbody->collider->UpdateTransform(scene.player_aabb.rigidbody->position, scene.player_aabb.rigidbody->rotation, scene.player_aabb.rigidbody->scale);
    scene.player_aabb.center = scene.player_aabb.rigidbody->position;
    //obstacle_2_aabb.rigidbody->collider->UpdateTransform(obstacle_2_aabb.rigidbody->position, obstacle_2_aabb.rigidbody->rotation, obstacle_2_aabb.rigidbody->scale);
    //obstacle_2_aabb.center = obstacle_2_aabb.rigidbody->position;
    scene.grid->RemoveObject(&(scene.player_aabb));
    //octree->RemoveObject(octree->root, &obstacle_2_aabb);
    scene.grid->InsertObject(&(scene.player_aabb));
    //octree->InsertObject(octree->root, &obstacle_2_aabb);
}*/

void Octree_Build(WIP_Polygon::Octree*& _octree, std::vector<WIP_Polygon::AABB*>_aabbs) {
    _octree = new WIP_Polygon::Octree(glm::vec3(0.0f), 5.0f, 3);

    for (int i = 0; i < _aabbs.size(); i++) {
        _octree->InsertObject(_octree->root, _aabbs[i]);
    }
}

void Octree_TestAllCollisions(WIP_Polygon::Node* _pTree, std::vector<std::pair <WIP_Polygon::AABB*, WIP_Polygon::AABB*>>& _aabb_pairs) {
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
                /*if (!pB->rigidbody->is_static) { 
                    //TestCollision(pB, pA);
                    _aabb_pairs.push_back(std::pair<WIP_Polygon::AABB*, WIP_Polygon::AABB*>(pB, pA));
                }
                else { 
                   //TestCollision(pA, pB); 
                   _aabb_pairs.push_back(std::pair<WIP_Polygon::AABB*, WIP_Polygon::AABB*>(pA, pB));
                } */      
                _aabb_pairs.push_back(std::pair<WIP_Polygon::AABB*, WIP_Polygon::AABB*>(pA, pB));

            }
        }
    }
    for (int i = 0; i < _pTree->pChild.size(); i++) {        
        if (_pTree->pChild[i]) {
            Octree_TestAllCollisions(_pTree->pChild[i], _aabb_pairs);
        }
    }
    depth--;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
    float xOffset = xPos - lastX;
    float yOffset = yPos - lastY;
    lastX = xPos;
    lastY = yPos;
    xOffset *= scene.camera->sensitivity;
    yOffset *= scene.camera->sensitivity;
    scene.camera->yaw += xOffset;
    scene.camera->pitch += yOffset;
}
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
    scene.camera->fov -= (float)yOffset;
    if (scene.camera->fov < 1.0f) {
        scene.camera->fov = 1.0f;
    }
    if (scene.camera->fov > 45.0f) {
        scene.camera->fov = 45.0f;
    }
}