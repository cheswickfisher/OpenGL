#ifndef DEBUG_H
#define DEBUG_H
#include <glad\glad.h>
#include <glfw3.h>
#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include "Shaders.h"
#include "HalfEdge.h"
#include "CollisionShape.h"
#include "Collider.h"
#include "AABB.h"
#include "Colors.h"
#include <vector>
#include <unordered_map>
namespace WIP_Polygon {
    class Collider;
    class AABB;
    struct DebugMesh {
        int id;
        unsigned int VAO;
        unsigned int VBO;

        std::vector<float> verts;
        Collider* collider;
        DebugMesh();
    };

    class Debug {
    public:
        std::unordered_map<int, DebugMesh> debug_meshes;
        Debug();
        void Setup();
        void AddMesh(WIP_Polygon::Collider* _collider);
        void UpdateTransforms(glm::mat4 view, glm::mat4 projection);
        void DrawDebugMeshes();
        static void DrawDebugLine(glm::vec3 start, glm::vec3 end, glm::vec4 color, float line_width);
        static void DrawDebugCube(glm::vec3 position, glm::quat rotation, glm::vec3 scale, glm::vec4 color, float line_width);
        static void DrawDebugSphere(glm::vec3 position, float radius, glm::vec4 color, float line_width);
        static void DrawAABB(AABB* aabb);
    private:
        void DefineCircleVerts(int _num_verts);
    };
}
#endif