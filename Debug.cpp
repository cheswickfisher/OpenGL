#include "Debug.h"

namespace WIP_Polygon {
    //Collider;
    DebugMesh::DebugMesh() :
        id{},
        VAO{},
        VBO{},
        verts{},
        collider{nullptr}
    {}
    unsigned int lineVAO{};
    unsigned int lineVBO{};
    unsigned int cubeVAO{};
    unsigned int cubeVBO{};
    unsigned int circleVAO{};
    unsigned int circleVBO{};

    std::vector<float> debug_line_verts = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    std::vector<float>debug_cube_verts = {   
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
    };
    std::vector<float>debug_circle_verts{};

    Debug::Debug() :
        debug_meshes{}
    {}

    std::vector<DebugMesh2> Debug::debug_meshes_2{};
    std::vector<DebugMesh2> Debug::debug_lines{};

	void Debug::Setup() {
        //line
        glGenVertexArrays(1, &lineVAO);
        glGenBuffers(1, &lineVBO);
        glBindVertexArray(lineVAO);
        glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
        glBufferData(GL_ARRAY_BUFFER, debug_line_verts.size() * sizeof(GLfloat), &debug_line_verts[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glBindVertexArray(0);
        //cube
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        glBindVertexArray(cubeVAO);
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, /*sizeof(debug_cube_verts)*/ debug_cube_verts.size() * sizeof(GLfloat), /*&debug_cube_verts*/&debug_cube_verts[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glBindVertexArray(0);
        //circle
        DefineCircleVerts(45);
        glGenVertexArrays(1, &circleVAO);
        glGenBuffers(1, &circleVBO);
        glBindVertexArray(circleVAO);
        glBindBuffer(GL_ARRAY_BUFFER, circleVAO);
        glBufferData(GL_ARRAY_BUFFER, debug_circle_verts.size() * sizeof(GLfloat), &debug_circle_verts[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glBindVertexArray(0);
	}    
    void Debug::AddMesh(WIP_Polygon::Collider* _collider) {
        CollisionShape* _mesh = _collider->collider;
        DebugMesh debug_mesh{};
        unsigned int VAO{};
        unsigned int VBO{};
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        debug_mesh.collider = _collider;
        debug_mesh.VAO = VAO;
        debug_mesh.VBO = VBO;
        debug_mesh.id = _mesh->id;
        int vert_count = _mesh->vertices.size();

        for (int i = 0; i < _mesh->planes.size(); i++) {
            WIP_Polygon::HalfEdge* start_edge = _mesh->planes[i].edge;
            WIP_Polygon::HalfEdge* current_edge = start_edge;
            do {
                debug_mesh.verts.push_back(current_edge->origin->position.x);
                debug_mesh.verts.push_back(current_edge->origin->position.y);
                debug_mesh.verts.push_back(current_edge->origin->position.z);
                current_edge = current_edge->next;
            } while (current_edge !=start_edge);
            //close off the mesh. may not work with meshes that are not closed?
            debug_mesh.verts.push_back(current_edge->origin->position.x);
            debug_mesh.verts.push_back(current_edge->origin->position.y);
            debug_mesh.verts.push_back(current_edge->origin->position.z);

        }
        glBufferData(GL_ARRAY_BUFFER, debug_mesh.verts.size() * sizeof(GLfloat), &debug_mesh.verts[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glBindVertexArray(0);

        debug_meshes[_mesh->id] = debug_mesh;
    }
    void Debug::UpdateTransforms(glm::mat4 view, glm::mat4 projection) {
        WIP_Polygon::Shaders::debugShader.use();
        WIP_Polygon::Shaders::debugShader.setMat4("view", view);
        WIP_Polygon::Shaders::debugShader.setMat4("projection", projection);
    }
    void Debug::DrawDebugLine(glm::vec3 start, glm::vec3 end, glm::vec4 color, float line_width) {
        
        std::vector<float>lineVertices = {
            start.x, start.y, start.z,
            end.x, end.y, end.z
        };
        glm::mat4 model = glm::mat4(1.0f);
        DebugMesh2 db2{};
        db2.VAO = lineVAO;
        db2.VBO = lineVBO;
        db2.localToWorld = model;
        db2.verts = lineVertices;
        db2.color = color;
        db2.line_width = line_width;
        debug_lines.push_back(db2);
    }
    void Debug::DrawDebugArrow(glm::vec3 start, glm::vec3 end, glm::vec4 color, float line_width) {
        float d = glm::length(end - start);
        glm::vec3 dir = glm::normalize(end - start);
        glm::vec3 p = dir * d * 0.9f;
        p.y = p.y + d * 0.01f;
        std::vector<float>lineVertices = {
            start.x, start.y, start.z,
            end.x, end.y, end.z,
            p.x, p.y, p.z
        };
        glm::mat4 model = glm::mat4(1.0f);
        DebugMesh2 db2{};
        db2.VAO = lineVAO;
        db2.VBO = lineVBO;
        db2.localToWorld = model;
        db2.verts = lineVertices;
        db2.color = color;
        db2.line_width = line_width;
        debug_lines.push_back(db2);
    }
    void Debug::DrawDebugLines() {
        for (int i = 0; i < debug_lines.size(); i++) {
            WIP_Polygon::Shaders::debugShader.use();
            WIP_Polygon::Shaders::debugShader.setMat4("model", glm::mat4(1.0f));
            WIP_Polygon::Shaders::debugShader.setVec4("color", debug_lines[i].color);
            glLineWidth(debug_lines[i].line_width);
            glBindVertexArray(lineVAO);
            glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
            glBufferData(GL_ARRAY_BUFFER, debug_lines[i].verts.size() * sizeof(GLfloat), &debug_lines[i].verts[0], GL_STATIC_DRAW);
            glDrawArrays(GL_LINE_STRIP, 0, debug_lines[i].verts.size() / 3);
            glBindVertexArray(0);
            glLineWidth(1.0f);
        }
        debug_lines.clear();
    }
    void Debug::DrawDebugCube(glm::vec3 position, glm::quat rotation, glm::vec3 scale, glm::vec4 color, float line_width) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position) * glm::toMat4(rotation) * glm::scale(model, scale);
        DebugMesh2 db2{};
        db2.VAO = cubeVAO;
        db2.VBO = cubeVBO;
        db2.localToWorld = model;
        db2.verts = debug_cube_verts;
        db2.vert_count = 24;
        db2.color = color;
        db2.line_width = line_width;
        debug_meshes_2.push_back(db2);
    }
    void Debug::DrawDebugSphere(glm::vec3 position, float radius, glm::vec4 color, float line_width) {
        glm::quat rot_X = glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::quat rot_Y = glm::angleAxis(glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position) * glm::scale(model, radius * glm::vec3(1.0f));
        WIP_Polygon::Shaders::debugShader.use();
        WIP_Polygon::Shaders::debugShader.setMat4("model", model);
        WIP_Polygon::Shaders::debugShader.setVec4("color", color);
        glLineWidth(line_width);
        glBindVertexArray(circleVAO);
        glDrawArrays(GL_LINE_STRIP, 0, debug_circle_verts.size() * 0.5f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, position) * glm::toMat4(rot_X) * glm::scale(model, radius * glm::vec3(1.0f));
        WIP_Polygon::Shaders::debugShader.setMat4("model", model);
        glDrawArrays(GL_LINE_STRIP, 0, debug_circle_verts.size() * 0.5f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, position) * glm::toMat4(rot_Y) * glm::scale(model, radius * glm::vec3(1.0f));
        WIP_Polygon::Shaders::debugShader.setMat4("model", model);
        glDrawArrays(GL_LINE_STRIP, 0, debug_circle_verts.size() * 0.5f);
        glBindVertexArray(0);
        glLineWidth(1.0f);
    }

    void Debug::DefineCircleVerts(int _num_verts) {
        _num_verts = glm::max(3, _num_verts);
        float step = 360.0f / static_cast<float>(_num_verts);
        std::vector<float>verts{};
        for (float i = 0.0f; i < 360.0f; i += step) {
            verts.push_back(glm::cos(glm::radians(i)));
            verts.push_back(glm::sin(glm::radians(i)));
        }
        verts.erase(verts.begin() + verts.size() - 1);
        verts.erase(verts.begin() + verts.size() - 1);
        verts.push_back(verts[0]);
        verts.push_back(verts[1]);
        debug_circle_verts = verts;
    }

    void Debug::DrawDebugMeshes() {
        std::unordered_map<int, DebugMesh>::iterator it;
        for (it = debug_meshes.begin(); it != debug_meshes.end(); it++) {
            WIP_Polygon::Shaders::debugShader.use();
            WIP_Polygon::Shaders::debugShader.setMat4("model", it->second.collider->m_localToWorld);
            WIP_Polygon::Shaders::debugShader.setVec4("color", it->second.collider->color);
            glLineWidth(1.0f);
            glBindVertexArray(it->second.VAO);
            glDrawArrays(GL_LINE_STRIP, 0, it->second.verts.size()/3);
            glBindVertexArray(0);
            glLineWidth(1.0f);
        }
    }
    void Debug::DrawDebugMeshes2() {
        for (int i = 0; i < debug_meshes_2.size(); i++) {
            WIP_Polygon::Shaders::debugShader.use();
            WIP_Polygon::Shaders::debugShader.setMat4("model", debug_meshes_2[i].localToWorld);
            WIP_Polygon::Shaders::debugShader.setVec4("color", debug_meshes_2[i].color);
            glLineWidth(debug_meshes_2[i].line_width);
            glBindVertexArray(debug_meshes_2[i].VAO);
            glDrawArrays(GL_LINE_STRIP, 0, debug_meshes_2[i].vert_count);
            glBindVertexArray(0);
            glLineWidth(1.0f);
        }
        debug_meshes_2.clear();
    }

}