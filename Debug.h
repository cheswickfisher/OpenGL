#ifndef DEBUG_H
#define DEBUG_H
#include <glad\glad.h>
#include <glfw3.h>
#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include "Shader.h"
#include "HalfEdge.h"
#include "CollisionShape.h"
#include "Collider.h"
//#include "Colors.h"
#include <vector>
#include <unordered_map>
//WIP_Polygon::Collider;
namespace WIP_Polygon {
    class Collider;
    struct DebugMesh {
        int id;
        unsigned int VAO;
        unsigned int VBO;
        std::vector<float> verts;
        Collider* collider;
        DebugMesh();
    };
    //float debug_line_verts[6] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
   /* float debug_cube_verts[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };*/
    //std::unordered_map<int, DebugMesh> debug_meshes;

    class Debug {
    public:
        std::unordered_map<int, DebugMesh> debug_meshes;
        Debug();
        /*Debug() {

        }*/
        void Setup(Shader _shader);
        /*void Setup(Shader _shader) {
            debugShader = _shader;
            //line
            glGenVertexArrays(1, &lineVAO);
            glGenBuffers(1, &lineVBO);
            glBindVertexArray(lineVAO);
            glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(debug_line_verts), &debug_line_verts, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glBindVertexArray(0);
            //cube
            glGenVertexArrays(1, &cubeVAO);
            glGenBuffers(1, &cubeVBO);
            glBindVertexArray(cubeVAO);
            glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(debug_cube_verts), &debug_cube_verts, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glBindVertexArray(0);
        }
        */
        void AddMesh(WIP_Polygon::Collider* _collider);
        /*void AddMesh(WIP_Polygon::CollisionShape* _mesh) {
            DebugMesh debug_mesh{};
            unsigned int VAO{};
            unsigned int VBO{};
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            debug_mesh.mesh = _mesh;
            debug_mesh.VAO = VAO;
            debug_mesh.VBO = VBO;
            int vert_count = _mesh->vertices.size();

            for (int i = 0; i < _mesh->planes.size(); i++) {
                WIP_Polygon::HalfEdge* start_edge = _mesh->planes[i].edge;
                WIP_Polygon::HalfEdge* current_edge = start_edge;
                do {
                    debug_mesh.verts.push_back(current_edge->origin->position.x);
                    debug_mesh.verts.push_back(current_edge->origin->position.y);
                    debug_mesh.verts.push_back(current_edge->origin->position.z);
                    current_edge = current_edge->next;
                } while (current_edge != start_edge);
            }
            glBufferData(GL_ARRAY_BUFFER, sizeof(debug_mesh.verts), &debug_mesh.verts, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glBindVertexArray(0);

            debug_meshes[_mesh->id] = debug_mesh;
        }*/
        void UpdateTransforms(glm::mat4 view, glm::mat4 projection);
        /*void UpdateTransforms(glm::mat4 view, glm::mat4 projection, std::vector<int> _debug_colliders) {
           debugShader.use();
            debugShader.setMat4("view", view);
            debugShader.setMat4("projection", projection);

            int count = _debug_colliders.size();
            glm::mat4 model = glm::mat4(1.0f);
            for (int i = 0; i < count; i++) {
                if (debug_meshes.find(_debug_colliders[i]->collider->id) == debug_meshes.end()) {
                    continue;
                }
                debug_meshes[_debug_colliders[i]->collider->id].model = glm::translate(model, _debug_colliders[i]->center)
                    * glm::toMat4(_debug_colliders[i]->rotation)
                    * glm::scale(model, _debug_colliders[i]->scale);
            }
        }*/
        void DrawDebugMeshes();
        /*static void DrawDebugMeshes() {
            std::unordered_map<int, DebugMesh>::iterator it;
            for (it = debug_meshes.begin(); it != debug_meshes.end(); it++) {
                debugShader.use();
                debugShader.setMat4("model", it->second.model);
                debugShader.setVec4("color", Colors::Green);
                glLineWidth(1.0f);
                glBindVertexArray(it->second.VAO);
                glDrawArrays(GL_LINE_STRIP, 0, it->second.mesh->edges.size());
                glBindVertexArray(0);
                glLineWidth(1.0f);
            }
        }*/
        static void DrawDebugLine(glm::vec3 start, glm::vec3 end, glm::vec4 color, float line_width);
        /*static void DrawDebugLine(glm::vec3 start, glm::vec3 end, glm::vec4 color, float line_width) {
            float lineVertices[] = {
            start.x, start.y, start.z,
            end.x, end.y, end.z
            };
            debugShader.use();
            debugShader.setMat4("model", glm::mat4(1.0f));
            debugShader.setVec4("color", color);
            glLineWidth(line_width);
            glBindVertexArray(lineVAO);
            glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), &lineVertices, GL_STATIC_DRAW);
            glDrawArrays(GL_LINE_LOOP, 0, 2);
            glBindVertexArray(0);
            glLineWidth(1.0f);
        }*/
        static void DrawDebugCube(glm::vec3 position, glm::quat rotation, glm::vec3 scale, glm::vec4 color, float line_width);
        /*static void DrawDebugCube(glm::vec3 position, glm::quat rotation, glm::vec3 scale, glm::vec4 color, float line_width) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, position) * glm::toMat4(rotation) * glm::scale(model, scale);
            debugShader.use();
            debugShader.setMat4("model", model);
            debugShader.setVec4("color", color);
            glLineWidth(line_width);
            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_LINE_STRIP, 0, 24);
            glBindVertexArray(0);
            glLineWidth(1.0f);
        }*/

    };
}
#endif