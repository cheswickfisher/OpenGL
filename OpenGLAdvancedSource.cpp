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
#include "Scenes\Scene_3.h"
#include "Scenes\Scene_4.h"
#include "Preferences.h"
#include "OBJImporter.h"

#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>
#include <glm\glm\gtc\quaternion.hpp>
#include <glm\glm\gtx\quaternion.hpp>

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#define IDENTITY_QUAT glm::quat(1.0f,0.0f,0.0f,0.0f)

void update();
void updatePhysics();
void render();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);

const float infinity = std::numeric_limits<float>::infinity();

float lastX = 960.0f;
float lastY = 540.0f;
float lastFrame = 0.0f;

Materials materials;
GLFWwindow* window;


/*glm::vec3 dirLightDirection(-0.2f, -1.0f, -0.3f);
glm::vec3 dirLightColor(1.0f, 1.0f, 1.0f);*/
WIP_Polygon::CollisionHandler collisionHandler;

//load scenes here
//WIP_Polygon::Scene_1 scene_1{};
//WIP_Polygon::Scene_3 scene_3{};
WIP_Polygon::Scene_4 scene_4{};
//set active scene here
WIP_Polygon::Scene& scene{ scene_4 };

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

    float accumulator = 0;
    float frame_start = static_cast<float>(glfwGetTime());

    std::cout << "start program" << "\n";
    while (!glfwWindowShouldClose(window)) {
        //std::cout << "start frame" << "\n";
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        accumulator += deltaTime;
        lastFrame = currentFrame;

        if (accumulator > 0.2f) {
            accumulator = 0.2f;
        }
        //WIP_Polygon::Debug::DrawDebugCube(glm::vec3(0.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(1.0f), Colors::White, 1.0f);

        scene.HandleInput(window);
        //moving this to after physics update, so input forces get applied only after collision forces are 
        //  accounted for.
        update();
        //std::cout << "start phys" << "\n";
        while (accumulator > fixed_dt) {
            updatePhysics();
            accumulator -= fixed_dt;
        }  
        //std::cout << "end phys" << "\n";
        //std::cout << "start render" << "\n";
        render();

        //std::cout << "end render" << "\n";
        //std::cout << "end frame" << "\n";
    }

    for (int i = 0; i < scene.mesh_renderers->size(); i++) {
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
    collisionHandler.UpdateSceneDynamicColliders2(scene);
}

void render() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    scene.DrawScene();

    glfwSwapBuffers(window);
    glfwPollEvents();
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