#include <glad\glad.h>
#include <glfw3.h>

#include "Materials.h"
//#include "Shader.h"
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

#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>
#include <glm\glm\gtc\quaternion.hpp>
#include <glm\glm\gtx\quaternion.hpp>

#include <iostream>
#include <string>
#include <utility>

#define IDENTITY_QUAT glm::quat(1.0f,0.0f,0.0f,0.0f)

void Update_Dynamic_Colliders();
void Octree_Update();
void Octree_Build(WIP_Polygon::Octree*& _octree, std::vector<WIP_Polygon::AABB*>_aabbs);
void ResolveCollisions(std::vector<std::pair <WIP_Polygon::AABB*, WIP_Polygon::AABB*>>& _aabb_pairs);
void TestCollision(WIP_Polygon::AABB* _pA, WIP_Polygon::AABB* _pB);
void Octree_TestAllCollisions(WIP_Polygon::Node* _pTree, std::vector<std::pair <WIP_Polygon::AABB*, WIP_Polygon::AABB*>>& _aabb_pairs);
void update();
void updatePhysics();
void render();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
void processInput(GLFWwindow* window);
bool checkOverlap(WIP_Polygon::Collider* a, WIP_Polygon::Collider* b, WIP_Polygon::ContactManifold& manifold);
void updateCameraTransform();
void loadTerrain(char const* path);


float fov = 45.0f;
const float SCREEN_WIDTH = 1360.0f;
const float SCREEN_HEIGHT = 768.0f;
float a = SCREEN_WIDTH / SCREEN_HEIGHT;
const float infinity = std::numeric_limits<float>::infinity();

Camera camera;
const float cameraSpeed = 5.0f;
const float sensitivity = 0.001f;
float lastX = 960.0f;
float lastY = 540.0f;
float pitch = 0.0f;
float yaw = 0.0f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

Materials materials;
WIP_Polygon::Debug debug;
GLFWwindow* window;

unsigned int planeVAO;
unsigned int cubeVAO;

WIP_Polygon::BoxCollider player_collider{ glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 180.0f, 0.0f)};
//WIP_Polygon::BoxCollider obstacle_collider{ glm::vec3(2.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f, 0.0f, 0.0f)};
//WIP_Polygon::BoxCollider obstacle_2_collider{ glm::vec3(0.5f), glm::vec3(1.8f,-0.75f, 0.8f), glm::vec3(0.0f, 45.0f, 0.0f) };
//WIP_Polygon::QuadCollider ground_collider{ glm::vec3(10.0f), glm::vec3(0.0f,-1.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)};
WIP_Polygon::CharacterControls playerObject{ glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 180.0f, 0.0f), 10.0f, &player_collider};
//WIP_Polygon::Rigidbody obstacle{ glm::vec3(2.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1000.0f, & obstacle_collider};
//WIP_Polygon::Rigidbody obstacle_2{ obstacle_2_collider.scale, obstacle_2_collider.center, glm::vec3(0.0f, 45.0f, 0.0f), 10.0f, &obstacle_2_collider };
//WIP_Polygon::Rigidbody plane{ ground_collider.scale, ground_collider.center, glm::vec3(90.0f, 0.0f, 0.0f), infinity, &ground_collider };
WIP_Polygon::AABB player_aabb{ &playerObject };
//WIP_Polygon::AABB obstacle_aabb{ &obstacle };
//WIP_Polygon::AABB obstacle_2_aabb{ &obstacle_2 };
//WIP_Polygon::AABB ground_aabb{ &plane };
WIP_Polygon::MeshRenderer player_mr{&WIP_Polygon::RenderShapes::cube, &WIP_Polygon::Shaders::lightingShader, &WIP_Polygon::Textures::rock_cliff_albedo.first, &playerObject};
//WIP_Polygon::MeshRenderer obstacle_mr{ &WIP_Polygon::RenderShapes::cube, &WIP_Polygon::Shaders::lightingShader, &WIP_Polygon::Textures::sandstone_brick_diffuse.first, &obstacle };
//WIP_Polygon::MeshRenderer obstacle_2_mr{ &WIP_Polygon::RenderShapes::cube, &WIP_Polygon::Shaders::lightingShader,&WIP_Polygon::Textures::sandstone_brick_diffuse.first, &obstacle_2 };
//WIP_Polygon::MeshRenderer plane_mr{ &WIP_Polygon::RenderShapes::plane, &WIP_Polygon::Shaders::lightingShader, &WIP_Polygon::Textures::pavement_diffuse.first, &plane };

std::vector<WIP_Polygon::AABB*>aabbs{
    &player_aabb/*, &obstacle_aabb, &obstacle_2_aabb, &ground_aabb*/
};

std::vector<WIP_Polygon::GameObject*>gameobjects{
    &playerObject/*,& obstacle,& obstacle_2,& plane*/
};

std::vector<WIP_Polygon::MeshRenderer*>mesh_renderers{
    &player_mr/*, &obstacle_mr, &obstacle_2_mr, &plane_mr*/
};

WIP_Polygon::TerrainVolume terrain_volume{glm::vec3(0.0f, 0.0f, 0.0f), 1.0f};

WIP_Polygon::Octree* octree;
CollisionHandler collisionHandler;
glm::vec3 dirLightDirection(-0.2f, -1.0f, -0.3f);
glm::vec3 dirLightColor(1.0f, 1.0f, 1.0f);

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
    //loadTerrain(WIP_Polygon::Textures::grid_cell_noise_0.second);
    terrain_volume.loadTerrain(WIP_Polygon::Textures::perlin_noise_0.second);

    player_aabb.rigidbody->is_static = false;
    //obstacle_2_aabb.rigidbody->is_static = false;

    for (int i = 0; i < mesh_renderers.size(); i++) {
        mesh_renderers[i]->SetupMesh();
    }

    debug = WIP_Polygon::Debug();
    debug.Setup();
    for (int i = 0; i < aabbs.size(); i++) {
        debug.AddMesh(aabbs[i]->rigidbody->collider);
    }

    //Octree_Build(octree, aabbs);

    playerObject.name = "player";
    playerObject.collider->aabb = &player_aabb;
    //obstacle.name = "obstacle";
    //obstacle_2.name = "obstacle_2";
    //plane.name = "ground_plane";


    const float fps = 100;
    const float fixed_dt = 1 / fps;
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

        processInput(window);

        update();

        while (accumulator > fixed_dt) {
            updatePhysics();
            accumulator -= fixed_dt;
        }

        render();
    }

    for (int i = 0; i < mesh_renderers.size(); i++) {
        glDeleteVertexArrays(1, &(*mesh_renderers[i]).VAO);
        glDeleteBuffers(1, &(*mesh_renderers[i]).VBO);
    }
    delete octree; // do i need to do this?
    glfwTerminate();
	return 0;
}

void update() {
    for (int i = 0; i < gameobjects.size(); i++) {
        if (!gameobjects[i]->is_static) {
            gameobjects[i]->UpdateTransform();
        }
    }
}

void updatePhysics() {
    Update_Dynamic_Colliders();
    //terrain_volume.insertObject(playerObject.collider->aabb);
    /*Octree_Update();
    std::vector<std::pair <WIP_Polygon::AABB*, WIP_Polygon::AABB*>> aabb_pairs{};
    Octree_TestAllCollisions(octree->root, aabb_pairs);
    ResolveCollisions(aabb_pairs);*/
}


void render() {
    updateCameraTransform();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.ViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(fov), a, 0.1f, 100.0f);

    debug.UpdateTransforms(view, projection);
   
    playerObject.collider->DrawAxes();
    debug.DrawDebugMeshes();
    player_aabb.ConstructFromPointSet(&player_collider);
    WIP_Polygon::Debug::DrawDebugCube(playerObject.collider->aabb->center, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), playerObject.collider->aabb->radius * 2.0f, Colors::Cyan, 1.0f);
    glm::vec3 min_corner = playerObject.collider->aabb->center - playerObject.collider->aabb->radius;
    WIP_Polygon::Debug::DrawDebugCube(min_corner, glm::quat(1.0f,0.0f,0.0f,0.0f), glm::vec3(0.1f), Colors::Red, 1.0f);
    std::vector<WIP_Polygon::Rigidbody*> collision_rbs = terrain_volume.GetCollisionCells(playerObject.collider->aabb);

    for (int i = 0; i < collision_rbs.size(); i++) {
        WIP_Polygon::Debug::DrawDebugCube(collision_rbs[i]->collider->center, IDENTITY_QUAT, collision_rbs[i]->collider->scale, Colors::Red, 10.0f);
    }
    /*WIP_Polygon::Debug::DrawDebugSphere(obstacle_2_aabb.center, obstacle_2_aabb.radius.x, Colors::Red, 2.0f);
    WIP_Polygon::Debug::DrawDebugSphere(obstacle_aabb.center, obstacle_aabb.radius.x, Colors::Red, 2.0f);
    WIP_Polygon::Debug::DrawDebugSphere(player_aabb.center, player_aabb.radius.x, Colors::Purple, 2.0f);
    WIP_Polygon::Debug::DrawDebugCube(player_aabb.pCurrentNode->center, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(player_aabb.pCurrentNode->halfWidth * 2.0f), Colors::Red, 10.0f);
    WIP_Polygon::Debug::DrawDebugCube(obstacle_2_aabb.pCurrentNode->center, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(obstacle_2_aabb.pCurrentNode->halfWidth * 2.0f), Colors::Blue, 10.0f);*/

    //octree->DrawOctree(octree->root, octree->levels, 0);
    terrain_volume.renderGrid();

    WIP_Polygon::Shaders::lightingShader.use();
    WIP_Polygon::Shaders::lightingShader.setMat4("view", view);
    WIP_Polygon::Shaders::lightingShader.setMat4("projection", projection);

    for (int i = 0; i < mesh_renderers.size(); i++) {
        mesh_renderers[i]->game_object->UpdateTransform();
        mesh_renderers[i]->DrawMesh();
    }    

    terrain_volume.renderTerrain();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void ResolveCollisions(std::vector<std::pair <WIP_Polygon::AABB*, WIP_Polygon::AABB*>>& _aabb_pairs) {
     glm::vec3 offset = glm::vec3(0.0f);
     bool overlap{};
     float total_pen{ std::numeric_limits<float>::max() };
     int iterations = 0;
     int max_iterations = 4;
     while (total_pen > 0.0f + 0.001f && iterations < max_iterations) {
         total_pen = 0.0f;
         for (int i = 0; i < _aabb_pairs.size(); i++) {
             //if (_aabb_pairs[i].first->rigidbody->is_static) { continue; }
             WIP_Polygon::Collider* collider_a = _aabb_pairs[i].first->rigidbody->collider;
             _aabb_pairs[i].first->center = _aabb_pairs[i].first->rigidbody->position;
             collider_a->UpdateTransform(_aabb_pairs[i].first->rigidbody->position, _aabb_pairs[i].first->rigidbody->rotation, _aabb_pairs[i].first->rigidbody->scale);             
             WIP_Polygon::Collider* collider_b = _aabb_pairs[i].second->rigidbody->collider;
             collider_b->UpdateTransform(_aabb_pairs[i].second->rigidbody->position, _aabb_pairs[i].second->rigidbody->rotation, _aabb_pairs[i].second->rigidbody->scale);
             collider_b->manifold = WIP_Polygon::ContactManifold();
             overlap = checkOverlap(collider_a, collider_b, collider_b->manifold) || overlap;
             offset = collider_b->manifold.contact_normal * glm::abs(collider_b->manifold.contact_penetration);
             float fr1 = _aabb_pairs[i].second->rigidbody->mass / (_aabb_pairs[i].first->rigidbody->mass + _aabb_pairs[i].second->rigidbody->mass);
             fr1 = glm::min(1.0f, fr1);
             float fr2 = _aabb_pairs[i].first->rigidbody->mass / (_aabb_pairs[i].first->rigidbody->mass + _aabb_pairs[i].second->rigidbody->mass);             
             fr2 = glm::min(1.0f, fr2);
             glm::vec3 offset_a = offset * fr1;
             glm::vec3 offset_b = -offset * fr2;
             total_pen += glm::abs(collider_b->manifold.contact_penetration);
             _aabb_pairs[i].first->rigidbody->move_delta = offset_a;
             _aabb_pairs[i].first->rigidbody->UpdateTransform();
             _aabb_pairs[i].first->center = _aabb_pairs[i].first->rigidbody->position;
             collider_a->UpdateTransform(_aabb_pairs[i].first->rigidbody->position, _aabb_pairs[i].first->rigidbody->rotation, _aabb_pairs[i].first->rigidbody->scale);
             _aabb_pairs[i].second->rigidbody->move_delta = offset_b;
             _aabb_pairs[i].second->rigidbody->UpdateTransform();
             _aabb_pairs[i].second->center = _aabb_pairs[i].second->rigidbody->position;
             collider_b->UpdateTransform(_aabb_pairs[i].second->rigidbody->position, _aabb_pairs[i].second->rigidbody->rotation, _aabb_pairs[i].second->rigidbody->scale);
         }
         iterations += 1;
     }

}

void Update_Dynamic_Colliders() {
    player_aabb.rigidbody->collider->UpdateTransform(player_aabb.rigidbody->position, player_aabb.rigidbody->rotation, player_aabb.rigidbody->scale);
    player_aabb.center = player_aabb.rigidbody->position;
}

void Terrain_Collision() {
    int x{};
    int y{};
    int z{};
    terrain_volume.insertObject(playerObject.collider->aabb, x, y, z);

}

void Octree_Update() {
    //update dynamic objects nodes in octree
    //TODO: collect dynamic objects in vector and loop through to update
    player_aabb.rigidbody->collider->UpdateTransform(player_aabb.rigidbody->position, player_aabb.rigidbody->rotation, player_aabb.rigidbody->scale);
    player_aabb.center = player_aabb.rigidbody->position;
    //obstacle_2_aabb.rigidbody->collider->UpdateTransform(obstacle_2_aabb.rigidbody->position, obstacle_2_aabb.rigidbody->rotation, obstacle_2_aabb.rigidbody->scale);
    //obstacle_2_aabb.center = obstacle_2_aabb.rigidbody->position;
    octree->RemoveObject(octree->root, &player_aabb);
    //octree->RemoveObject(octree->root, &obstacle_2_aabb);
    octree->InsertObject(octree->root, &player_aabb);
    //octree->InsertObject(octree->root, &obstacle_2_aabb);
}

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

void TestCollision(WIP_Polygon::AABB* _pA, WIP_Polygon::AABB* _pB) {
    glm::vec3 initial_pos = _pA->rigidbody->position;
    glm::vec3 offset = glm::vec3(0.0f);
    bool overlap{};
    float total_pen{ std::numeric_limits<float>::max() };
    int iterations = 0;
    int max_iterations = 4;
    while (total_pen > 0.0f + 0.001f && iterations < max_iterations) {
        total_pen = 0.0f;
        WIP_Polygon::Collider* collider_a = _pA->rigidbody->collider;
        _pA->center = _pA->rigidbody->position;
        collider_a->UpdateTransform(_pA->rigidbody->position, _pA->rigidbody->rotation, _pA->rigidbody->scale);
        WIP_Polygon::Collider* collider_b = _pB->rigidbody->collider;
        collider_b->UpdateTransform(_pB->rigidbody->position, _pB->rigidbody->rotation, _pB->rigidbody->scale);
        collider_b->manifold = WIP_Polygon::ContactManifold();
        overlap = checkOverlap(collider_a, collider_b, collider_b->manifold) || overlap;
        offset = collider_b->manifold.contact_normal * glm::abs(collider_b->manifold.contact_penetration);
        total_pen += glm::abs(collider_b->manifold.contact_penetration);
        _pA->rigidbody->move_delta = offset;
        _pA->rigidbody->UpdateTransform();
        _pA->center = _pA->rigidbody->position;
        collider_a->UpdateTransform(_pA->rigidbody->position, _pA->rigidbody->rotation, _pA->rigidbody->scale);

        iterations += 1;
    }
    /* glm::vec3 initial_player_pos = playerObject.position;
     glm::vec3 offset = glm::vec3(0.0f);
     bool overlap{};
     float total_pen{ std::numeric_limits<float>::max() };
     int iterations = 0;
     int max_iterations = 4;
     while (total_pen > 0.0f + 0.001f && iterations < max_iterations) {
         total_pen = 0.0f;
         for (int i = 0; i < aabbs.size(); i++) {
             if (aabbs[i]->rigidbody->is_static) { continue; }
             WIP_Polygon::Collider* collider_a = aabbs[i]->rigidbody->collider;
             aabbs[i]->center = aabbs[i]->rigidbody->position;
             collider_a->UpdateTransform(aabbs[i]->rigidbody->position, aabbs[i]->rigidbody->rotation, aabbs[i]->rigidbody->scale);
             for (int j = 0; j < aabbs.size(); j++) {
                 if (aabbs[i]->rigidbody->collider->collider->id == aabbs[j]->rigidbody->collider->collider->id) { continue; }
                 WIP_Polygon::Collider* collider_b = aabbs[j]->rigidbody->collider;
                 collider_b->UpdateTransform(aabbs[j]->rigidbody->position, aabbs[j]->rigidbody->rotation, aabbs[j]->rigidbody->scale);
                 collider_b->manifold = WIP_Polygon::ContactManifold();
                 overlap = checkOverlap(collider_a, collider_b, collider_b->manifold) || overlap;
                 offset = collider_b->manifold.contact_normal * glm::abs(collider_b->manifold.contact_penetration);
                 total_pen += glm::abs(collider_b->manifold.contact_penetration);
                 aabbs[i]->rigidbody->move_delta = offset;
                 aabbs[i]->rigidbody->UpdateTransform();
                 aabbs[i]->center = aabbs[i]->rigidbody->position;
                 collider_a->UpdateTransform(aabbs[i]->rigidbody->position, aabbs[i]->rigidbody->rotation, aabbs[i]->rigidbody->scale);
             }
         }
         iterations += 1;
     }*/
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
    float xOffset = xPos - lastX;
    float yOffset = yPos - lastY;
    lastX = xPos;
    lastY = yPos;
    xOffset *= camera.sensitivity;
    yOffset *= camera.sensitivity;
    camera.yaw += xOffset;
    camera.pitch += yOffset;
}
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
    fov -= (float)yOffset;
    if (fov < 1.0f) {
        fov = 1.0f;
    }
    if (fov > 45.0f) {
        fov = 45.0f;
    }
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        playerObject.move_delta = playerObject.Forward() * deltaTime * playerObject.moveSpeed;        
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        playerObject.move_delta = -playerObject.Forward() * deltaTime * playerObject.moveSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        playerObject.yaw_delta = playerObject.turnSpeed * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        playerObject.yaw_delta = -playerObject.turnSpeed * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        playerObject.pitch_delta = playerObject.turnSpeed * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        playerObject.pitch_delta = -playerObject.turnSpeed * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        playerObject.roll_delta = playerObject.turnSpeed * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        playerObject.roll_delta = -playerObject.turnSpeed * deltaTime;
    }


}

void broadphase() {
    
}

bool checkOverlap(WIP_Polygon::Collider* a, WIP_Polygon::Collider* b, WIP_Polygon::ContactManifold& manifold) {
    bool overlap = collisionHandler.Overlap(a, b, manifold);
    return overlap;
}

void updateCameraTransform() {
    camera.UpdateRotation();
    camera.UpdatePosition(playerObject.position);
}

void loadTerrain(char const* path) {
    unsigned int textureID;
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        /*formula for accessing pixel(x, y) =
        *   data + y * width + x * nrChannels
        * formula for accessing pixel(x, y) of arbitrary sized grid_noise terrain texture
        *   center = (width / num_cells_per_row) / 2
        *   data + y * width + center * (2 * x + 1) * nrChannels
        * 
        * example for accessing single channel alpha value of pixel (cell, row)
        *   int row = 3;
            int cell = 6;
            int x = center_x * (2 * cell + 1);
            int y = width * center_y * (row * 2 + 1);
            int alpha = int(*(data + y + x * 1));
            std::cout << alpha << "\n";
            std::cout << "x-> " << width << " y-> " << height << " channels-> " << nrChannels << "\n";

        */
        int cells_per_row = 10;
        int center_x = (width / cells_per_row) / 2;
        int center_y = (height / cells_per_row) / 2;
        for (int z = 0; z < cells_per_row; z++) {
            for (int x = 0; x < cells_per_row; x++) {
                int i = center_x * (2 * x + 1);
                int j = center_y * width * (2 * z + 1);
                int alpha = int(*(data + z + x));
                int k = glm::mix(0, cells_per_row, static_cast<float>(alpha / 255));
                for (int y = 0; y < k; y++) {
                    //terrain[x][y][z] = WIP_Polygon::Rigidbody{glm::vec3(1.0f), glm::vec3(0.0f)};
                }
            }
        }
    }
    stbi_image_free(data);
}

/*unsigned int loadTexture(char const* path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (nrChannels == 1) {
            format = GL_RED;
        }
        else if (nrChannels == 3) {
            format = GL_RGB;
        }
        else if (nrChannels == 4) {
            format = GL_RGBA;
        }
        else {
            format = 0;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else {
        std::cout << "FAILED TO LOAD TEXTURE" << '\n';
    }
    stbi_image_free(data);
    return textureID;
return 0;
}*/
