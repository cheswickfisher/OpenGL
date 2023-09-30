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

#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>
#include <glm\glm\gtc\quaternion.hpp>
#include <glm\glm\gtx\quaternion.hpp>

#include <iostream>
#include <string>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
void processInput(GLFWwindow* window);
//void checkCollision(WIP_Polygon::BoxCollider a, WIP_Polygon::BoxCollider b, glm::vec3& offset);
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
WIP_Polygon::BoxCollider player_collider{ glm::vec3(0.5f), glm::vec3(0.0f,0.0f,0.0f) };
WIP_Polygon::BoxCollider obstacle_collider{ glm::vec3(2.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f, 0.0f, 0.0f)};
WIP_Polygon::BoxCollider obstacle_2_collider{ glm::vec3(0.8f), glm::vec3(1.8f,-0.6f, 0.9f), glm::vec3(0.0f, 0.0f, 0.0f) };
WIP_Polygon::QuadCollider ground_collider{ glm::vec3(10.0f), glm::vec3(0.0f,-1.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)};
CharacterControls playerObject{ glm::vec3(0.5f), glm::vec3(0.0f, -0.75f, 2.0f), glm::vec3(0.0f, 180.0f, 0.0f), &player_collider};
Rigidbody obstacle{ glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 0.0f), &obstacle_collider};
Rigidbody obstacle_2{ glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 0.0f), &obstacle_2_collider };
Rigidbody plane{ glm::vec3(1.0f), glm::vec3(0.0f, 0.0, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),&ground_collider};
GameObject debugCollider{ glm::vec3(0.1f), glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f) };
std::vector<WIP_Polygon::Collider*>colliders{
    &player_collider, &obstacle_collider, &obstacle_2_collider, &ground_collider
};
CollisionHandler collisionHandler;
glm::vec3 dirLightDirection(-0.2f, -1.0f, -0.3f);
glm::vec3 dirLightColor(1.0f, 1.0f, 1.0f);

Materials materials;

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
float planeVertices[] = {
    // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
     5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

     5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
     5.0f, -0.5f, -5.0f,  2.0f, 2.0f
};
int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGLAdvanced", NULL, NULL);
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

    Shader lightingShader("C:/OPENGL/shaders/depth_testing.vs", "C:/OPENGL/shaders/depth_testing.fs");
    Shader debugShader("C:/OPENGL/shaders/debug_lines.vs", "C:/OPENGL/shaders/debug_lines.fs");

    glEnable(GL_DEPTH_TEST);

    unsigned int cubeVAO, cubeVBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);

    unsigned int planeVAO, planeVBO;
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);  
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
    glBindVertexArray(0);

    unsigned int lineVAO, lineVBO;
    float lineVertices[] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };
    glGenVertexArrays(1, &lineVAO);
    glGenBuffers(1, &lineVBO);
    glBindVertexArray(lineVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), &lineVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);

    WIP_Polygon::Debug debug = WIP_Polygon::Debug();
    debug.Setup(debugShader);
    for (int i = 0; i < colliders.size(); i++) {
        debug.AddMesh(colliders[i]);
    }

    unsigned int cubeTexture = loadTexture("C:/OPENGL/textures/sandstone_brick_wall_diffuse.png");
    unsigned int planeTexture = loadTexture("C:/OPENGL/textures/pavement_diffuse.png");
    unsigned int playerTexture = loadTexture("C:/OPENGL/textures/Rock_CliffLayered_albedo.png");

    lightingShader.setInt("texture1", 0);

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.ViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(fov), a, 0.1f, 100.0f);

        processInput(window);
        updateTransforms();

        glm::vec3 initial_player_pos = playerObject.position;
        glm::vec3 offset = glm::vec3(0.0f);
        glm::vec3 combined_offset{}; //using this for debugging
        WIP_Polygon::ContactManifold manifold{};
        bool overlap{};
        float total_pen{std::numeric_limits<float>::max()};
        int iterations = 0;
        while (total_pen > 0.0f + 0.001f) {
            total_pen = 0.0f;
            for (int i = 0; i < colliders.size(); i++) {
                if (playerObject.collider->collider->id == colliders[i]->collider->id) { continue; }
                overlap = checkOverlap(playerObject.collider, colliders[i], manifold) || overlap;
                offset = manifold.contact_normal * glm::abs(manifold.contact_penetration);
                playerObject.position = playerObject.position + offset;
                combined_offset += offset;
                total_pen += glm::abs(manifold.contact_penetration);
                manifold = WIP_Polygon::ContactManifold();
                updateTransforms();
            }
            iterations += 1;
        }
        std::cout << "solver iterations: " << iterations << "\n";
        if (overlap) {
            playerObject.collider->color = Colors::Red;
        }
        if (!overlap) {
            playerObject.collider->color = Colors::Green;
        }

        glm::vec4 col{};
        updateTransforms();
        updateCameraTransform();
        debug.UpdateTransforms(view, projection);

        playerObject.collider->DrawAxes();

        //debugCollider.position = initial_player_pos + combined_offset;
        
        debug.DrawDebugMeshes();

        lightingShader.use();
        lightingShader.setMat4("view", view);
        lightingShader.setMat4("projection", projection);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cubeTexture);
        model = glm::mat4(1.0f);
        model = glm::translate(model, obstacle.position);
        lightingShader.setMat4("model", model);
       //glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glBindTexture(GL_TEXTURE_2D, playerTexture);
        model = glm::mat4(1.0f);
        model =  glm::translate(model, playerObject.position) * glm::toMat4(playerObject.rotation) * glm::scale(model, playerObject.scale);
        lightingShader.setMat4("model", model);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(planeVAO);
        glBindTexture(GL_TEXTURE_2D, planeTexture);
        lightingShader.setMat4("model", glm::mat4(1.0f));
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteVertexArrays(1, &planeVAO);
    glDeleteBuffers(1, &planeVBO);

    glfwTerminate();
	return 0;
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

/*void checkCollision(WIP_Polygon::BoxCollider a, WIP_Polygon::BoxCollider b, glm::vec3& offset) {
    offset = collisionHandler.TestOBBOBB_3(a, b);
}*/

bool checkOverlap(WIP_Polygon::Collider* a, WIP_Polygon::Collider* b, WIP_Polygon::ContactManifold& manifold) {
    bool overlap = collisionHandler.Overlap(a, b, manifold);
    return overlap;
}

void updateTransforms() {
    playerObject.UpdateRotation();
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
