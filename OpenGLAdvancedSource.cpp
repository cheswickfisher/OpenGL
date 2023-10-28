#include <glad\glad.h>
#include <glfw3.h>

#include "Materials.h"
#include "Shader.h"
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

#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>
#include <glm\glm\gtc\quaternion.hpp>
#include <glm\glm\gtx\quaternion.hpp>

#include <iostream>
#include <string>

void TestCollision(WIP_Polygon::AABB* _pA, WIP_Polygon::AABB* _pB);
void TestAllCollisions(WIP_Polygon::Node* _pTree);
void update();
void updatePhysics();
void render();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
void processInput(GLFWwindow* window);
bool checkOverlap(WIP_Polygon::Collider* a, WIP_Polygon::Collider* b, WIP_Polygon::ContactManifold& manifold);
void updateCameraTransform();
//void updateTransforms();
unsigned int loadTexture(char const* path);

float fov = 45.0f;
const float SCREEN_WIDTH = 1360.0f;
const float SCREEN_HEIGHT = 768.0f;
float a = SCREEN_WIDTH / SCREEN_HEIGHT;

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
Shader lightingShader;
Shader debugShader;
GLFWwindow* window;
unsigned int cubeTexture;
unsigned int planeTexture;
unsigned int playerTexture;
unsigned int planeVAO;
unsigned int cubeVAO;

WIP_Polygon::BoxCollider player_collider{ glm::vec3(0.5f), glm::vec3(-2.0f, -0.75f, 2.0f), glm::vec3(0.0f, 180.0f, 0.0f)};
WIP_Polygon::BoxCollider obstacle_collider{ glm::vec3(2.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f, 0.0f, 0.0f)};
WIP_Polygon::BoxCollider obstacle_2_collider{ glm::vec3(0.5f), glm::vec3(1.8f,-0.75f, 0.8f), glm::vec3(0.0f, 45.0f, 0.0f) };
WIP_Polygon::QuadCollider ground_collider{ glm::vec3(10.0f), glm::vec3(0.0f,-1.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)};
WIP_Polygon::CharacterControls playerObject{ glm::vec3(0.5f), glm::vec3(-2.0f, -0.75f, 2.0f), glm::vec3(0.0f, 180.0f, 0.0f), &player_collider};
WIP_Polygon::Rigidbody obstacle{ glm::vec3(2.0f), glm::vec3(0.0f, 0.0f, 0.0f), &obstacle_collider};
WIP_Polygon::Rigidbody obstacle_2{ obstacle_2_collider.scale, obstacle_2_collider.center, glm::vec3(0.0f, 45.0f, 0.0f),&obstacle_2_collider };
WIP_Polygon::Rigidbody plane{ ground_collider.scale, ground_collider.center, glm::vec3(90.0f, 0.0f, 0.0f), &ground_collider };
WIP_Polygon::AABB player_aabb{ &playerObject };
WIP_Polygon::AABB obstacle_aabb{ &obstacle };
WIP_Polygon::AABB obstacle_2_aabb{ &obstacle_2 };
WIP_Polygon::AABB ground_aabb{ &plane };
WIP_Polygon::MeshRenderer player_mr{&WIP_Polygon::RenderShapes::cube, &lightingShader, &playerTexture, &playerObject};
WIP_Polygon::MeshRenderer obstacle_mr{ &WIP_Polygon::RenderShapes::cube, &lightingShader, &cubeTexture, &obstacle };
WIP_Polygon::MeshRenderer obstacle_2_mr{ &WIP_Polygon::RenderShapes::cube, &lightingShader, &cubeTexture, &obstacle_2 };
WIP_Polygon::MeshRenderer plane_mr{ &WIP_Polygon::RenderShapes::plane, &lightingShader, &planeTexture, &plane };

std::vector<WIP_Polygon::AABB*>aabbs{
    &player_aabb, &obstacle_aabb, &obstacle_2_aabb, &ground_aabb
};

std::vector<WIP_Polygon::GameObject*>gameobjects{
    &playerObject, &obstacle, &obstacle_2, &plane
};

std::vector<WIP_Polygon::MeshRenderer*>mesh_renderers{
    &player_mr, &obstacle_mr, &obstacle_2_mr, &plane_mr
};
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

    lightingShader = Shader("C:/OPENGL/shaders/depth_testing.vs", "C:/OPENGL/shaders/depth_testing.fs");
    debugShader = Shader("C:/OPENGL/shaders/debug_lines.vs", "C:/OPENGL/shaders/debug_lines.fs");

    glEnable(GL_DEPTH_TEST);

    player_aabb.rigidbody->is_static = false;

    for (int i = 0; i < mesh_renderers.size(); i++) {
        mesh_renderers[i]->SetupMesh();
    }

    debug = WIP_Polygon::Debug();
    debug.Setup(debugShader);
    for (int i = 0; i < aabbs.size(); i++) {
        debug.AddMesh(aabbs[i]->rigidbody->collider);
    }

    octree = new WIP_Polygon::Octree(glm::vec3(0.0f), 5.0f, 3);
    octree->InsertObject(octree->root, &player_aabb);
    octree->InsertObject(octree->root, &obstacle_aabb);
    octree->InsertObject(octree->root, &obstacle_2_aabb);
    octree->InsertObject(octree->root, &ground_aabb);

    cubeTexture = loadTexture(WIP_Polygon::Textures::sandstone_brick_diffuse);
    planeTexture = loadTexture(WIP_Polygon::Textures::pavement_diffuse);
    playerTexture = loadTexture(WIP_Polygon::Textures::rock_cliff_albedo);

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
    //update dynamic objects nodes in octree
    player_aabb.rigidbody->collider->UpdateTransform(player_aabb.rigidbody->position, player_aabb.rigidbody->rotation, player_aabb.rigidbody->scale);
    player_aabb.center = player_aabb.rigidbody->position;
    octree->RemoveObject(octree->root, &player_aabb);
    octree->InsertObject(octree->root, &player_aabb);

    TestAllCollisions(octree->root);
    /*glm::vec3 initial_player_pos = playerObject.position;
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
    WIP_Polygon::Debug::DrawDebugSphere(obstacle_2_aabb.center, obstacle_2_aabb.radius.x, Colors::Red, 2.0f);
    WIP_Polygon::Debug::DrawDebugSphere(obstacle_aabb.center, obstacle_aabb.radius.x, Colors::Red, 2.0f);
    WIP_Polygon::Debug::DrawDebugSphere(player_aabb.center, player_aabb.radius.x, Colors::Purple, 2.0f);
    WIP_Polygon::Debug::DrawDebugCube(player_aabb.pCurrentNode->center, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(player_aabb.pCurrentNode->halfWidth * 2.0f), Colors::Red, 10.0f);
    WIP_Polygon::Debug::DrawDebugCube(obstacle_2_aabb.pCurrentNode->center, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(obstacle_2_aabb.pCurrentNode->halfWidth * 2.0f), Colors::Blue, 10.0f);

    octree->DrawOctree(octree->root, octree->levels, 0);

    lightingShader.use();
    lightingShader.setMat4("view", view);
    lightingShader.setMat4("projection", projection);

    for (int i = 0; i < mesh_renderers.size(); i++) {
        mesh_renderers[i]->game_object->UpdateTransform();
        mesh_renderers[i]->DrawMesh();
    }    

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void TestAllCollisions(WIP_Polygon::Node* _pTree) {
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
                if (!pB->rigidbody->is_static) { TestCollision(pB, pA); }
                else { TestCollision(pA, pB); }                  
            }
        }
    }
    for (int i = 0; i < _pTree->pChild.size(); i++) {        
        if (_pTree->pChild[i]) {
            TestAllCollisions(_pTree->pChild[i]);
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

unsigned int loadTexture(char const* path) {
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
}
