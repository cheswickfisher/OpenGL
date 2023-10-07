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

#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>
#include <glm\glm\gtc\quaternion.hpp>
#include <glm\glm\gtx\quaternion.hpp>

#include <iostream>
#include <string>

void updatePhysics();
void render();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
void processInput(GLFWwindow* window);
bool checkOverlap(WIP_Polygon::Collider* a, WIP_Polygon::Collider* b, WIP_Polygon::ContactManifold& manifold);
void updateCameraTransform();
void updateTransforms();
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

float cubeVertices[] = {
    // positions          // texture Coords
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
std::vector<float>cube_verts = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
float planeVertices[] = {
    // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
     5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

     5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
     5.0f, -0.5f, -5.0f,  2.0f, 2.0f
};

WIP_Polygon::BoxCollider player_collider{ glm::vec3(0.5f), glm::vec3(0.0f,0.0f,0.0f) };
WIP_Polygon::BoxCollider obstacle_collider{ glm::vec3(2.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f, 0.0f, 0.0f)};
WIP_Polygon::BoxCollider obstacle_2_collider{ glm::vec3(0.8f), glm::vec3(1.8f,-0.6f, 0.8f), glm::vec3(0.0f, 45.0f, 0.0f) };
WIP_Polygon::QuadCollider ground_collider{ glm::vec3(10.0f), glm::vec3(0.0f,-1.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)};
CharacterControls playerObject{ glm::vec3(0.5f), glm::vec3(0.0f, -0.75f, 2.0f), glm::vec3(0.0f, 180.0f, 0.0f), &player_collider};
Rigidbody obstacle{ glm::vec3(2.0f), glm::vec3(0.0f, 0.0f, 0.0f), &obstacle_collider};
Rigidbody obstacle_2{ obstacle_2_collider.scale, obstacle_2_collider.center, glm::vec3(0.0f, 45.0f, 0.0f),&obstacle_2_collider };
Rigidbody plane{ ground_collider.scale, ground_collider.center, glm::vec3(90.0f, 0.0f, 0.0f), &ground_collider };
GameObject debugCollider{ glm::vec3(0.1f), glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f) };
WIP_Polygon::MeshRenderer player_mr{&WIP_Polygon::RenderShapes::cube, &lightingShader, &playerTexture, &playerObject};
WIP_Polygon::MeshRenderer obstacle_mr{ &WIP_Polygon::RenderShapes::cube, &lightingShader, &cubeTexture, &obstacle };
WIP_Polygon::MeshRenderer obstacle_2_mr{ &WIP_Polygon::RenderShapes::cube, &lightingShader, &cubeTexture, &obstacle_2 };
WIP_Polygon::MeshRenderer plane_mr{ &WIP_Polygon::RenderShapes::plane, &lightingShader, &planeTexture, &plane };

std::vector<WIP_Polygon::Collider*>colliders{
    &player_collider, &obstacle_collider, &obstacle_2_collider, &ground_collider
};

std::vector<WIP_Polygon::MeshRenderer*>mesh_renderers{
    &player_mr, &obstacle_mr, &obstacle_2_mr, &plane_mr
};

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

    player_collider.is_static = false;

    for (int i = 0; i < mesh_renderers.size(); i++) {
        mesh_renderers[i]->SetupMesh();
    }

    debug = WIP_Polygon::Debug();
    debug.Setup(debugShader);
    for (int i = 0; i < colliders.size(); i++) {
        debug.AddMesh(colliders[i]);
    }

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

void updatePhysics() {
    updateTransforms();
    glm::vec3 initial_player_pos = playerObject.position;
    glm::vec3 offset = glm::vec3(0.0f);
    bool overlap{};
    float total_pen{ std::numeric_limits<float>::max() };
    int iterations = 0;
    int max_iterations = 4;
    while (total_pen > 0.0f + 0.001f && iterations < max_iterations) {
        total_pen = 0.0f;
        for (int i = 0; i < colliders.size(); i++) {
            if (playerObject.collider->collider->id == colliders[i]->collider->id) { continue; }
            colliders[i]->manifold = WIP_Polygon::ContactManifold();
            overlap = checkOverlap(playerObject.collider, colliders[i], colliders[i]->manifold) || overlap;
            offset = colliders[i]->manifold.contact_normal * glm::abs(colliders[i]->manifold.contact_penetration);
            playerObject.position = playerObject.position + offset;
            total_pen += glm::abs(colliders[i]->manifold.contact_penetration);
            updateTransforms();
        }
        iterations += 1;
    }
}

void render() {
    updateCameraTransform();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.ViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(fov), a, 0.1f, 100.0f);

    updateCameraTransform();
    debug.UpdateTransforms(view, projection);

    playerObject.collider->DrawAxes();

    debug.DrawDebugMeshes();
    
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
        playerObject.position += playerObject.Forward() * deltaTime * playerObject.moveSpeed;        
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        playerObject.position += -playerObject.Forward() * deltaTime * playerObject.moveSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        playerObject.yaw_delta += playerObject.turnSpeed * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        playerObject.yaw_delta -= playerObject.turnSpeed * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        playerObject.pitch_delta += playerObject.turnSpeed * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        playerObject.pitch_delta -= playerObject.turnSpeed * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        playerObject.roll_delta += playerObject.turnSpeed * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        playerObject.roll_delta -= playerObject.turnSpeed * deltaTime;
    }


}

bool checkOverlap(WIP_Polygon::Collider* a, WIP_Polygon::Collider* b, WIP_Polygon::ContactManifold& manifold) {
    bool overlap = collisionHandler.Overlap(a, b, manifold);
    return overlap;
}

void updateTransforms() {
    playerObject.UpdateTransform();
    playerObject.collider->UpdateTransform(playerObject.position, playerObject.rotation, playerObject.scale);
    debugCollider.rotation = playerObject.rotation;
    obstacle.collider->center = obstacle.position;
    playerObject.collider->center = playerObject.position;
    playerObject.collider->aabb.center = playerObject.position;
    playerObject.collider->rotation = playerObject.rotation;
    playerObject.collider->u[0] = glm::normalize(playerObject.collider->rotation * glm::vec3(1.0f, 0.0f, 0.0f));
    playerObject.collider->u[1] = glm::normalize(playerObject.collider->rotation * glm::vec3(0.0f, 1.0f, 0.0f));
    playerObject.collider->u[2] = glm::normalize(playerObject.collider->rotation * glm::vec3(0.0f, 0.0f, 1.0f));
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
