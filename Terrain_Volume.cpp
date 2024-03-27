#include "Terrain_Volume.h"

namespace WIP_Polygon {
	TerrainVolume::TerrainVolume() {}

    TerrainVolume::TerrainVolume(glm::vec3 _position, float _cube_scale_factor) :
        position{ _position }, terrain_scale_factor{ num_cubes_xyz * _cube_scale_factor }, cube_scale_factor{ _cube_scale_factor }, localToWorld {
            glm::translate(glm::mat4(1.0f), _position)*
            glm::scale(glm::mat4(1.0f), glm::vec3(static_cast<float>(terrain_scale_factor))),
        }, terrain{}
    {}
    void TerrainVolume::loadTerrain(char const* path) {
        unsigned int textureID;
        int width, height, nrChannels;
        unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
        //if (data) {
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
            /*int center_x = (width / cells_per_row) / 2;
            int center_z = (height / cells_per_row) / 2;
            glm::vec3 increment = glm::vec3(1.0f / static_cast<float>(cells_per_row));
            TerrainVolume::cube_scale = static_cast<float>(terrain_scale) / static_cast<float>(cells_per_row);
            //glm::vec3 start_pos = glm::vec3(static_cast<float>(terrain_scale) * -0.5f);
            glm::vec3 start_pos = glm::vec3(-0.5) + increment * 0.5f;

            std::cout << "start_pos-> " << "(" << start_pos.x << "," << start_pos.y << "," << start_pos.z << ")\n";
            glm::vec3 current_pos = start_pos;
            int num_cubes = 0;
            for (int z = 0; z < cells_per_row; z++) {
                for (int x = 0; x < cells_per_row; x++) {
                    int i = center_x * (2 * x + 1);
                    int j = center_z * width * (2 * z + 1);
                    int alpha = int(*(data + j + i));
                    int k = glm::mix(0, cells_per_row, static_cast<float>(alpha) / static_cast<float>(255));
                    for (int y = 0; y < k; y++) {
                        glm::vec3 local_pos = glm::vec3(current_pos.x, current_pos.y, current_pos.z);
                        glm::vec3 world_pos = localToWorld * glm::vec4(local_pos, 1.0f);
                        terrain[x][y][z] = WIP_Polygon::Rigidbody{glm::vec3(cube_scale), world_pos, std::numeric_limits<float>::infinity(), new BoxCollider(glm::vec3(cube_scale), world_pos, glm::vec3(0.0f, 0.0f, 0.0f))};
                        terrain[x][y][z].mesh_renderer = new WIP_Polygon::MeshRenderer(&WIP_Polygon::RenderShapes::cube, &WIP_Polygon::Shaders::lightingShader, &WIP_Polygon::Textures::sandstone_brick_diffuse.first, &terrain[x][y][z]);
                        terrain[x][y][z].mesh_renderer->SetupMesh();
                        current_pos = glm::vec3(current_pos.x, current_pos.y + increment.y, current_pos.z);
                    }
                    current_pos = glm::vec3(current_pos.x + increment.x, start_pos.y, current_pos.z);
                }
                current_pos = glm::vec3(start_pos.x, start_pos.y, current_pos.z + increment.z);
            }*/

        //}

        /*for (int z = 0; z < num_cubes_xyz; z++) {
            for (int x = 0; x < num_cubes_xyz; x++) {
                for (int y = 0; y < num_cubes_xyz; y++) {
                    terrain[x][y][z] = nullptr;
                }
            }
        }*/

        if (data) {
            //float cube_scale_factor = 1.0f;
            //float terrain_scale_factor = num_cubes_xyz * cube_scale_factor;
            glm::vec3 increment = glm::vec3(1.0f / static_cast<float>(num_cubes_xyz));
            glm::vec3 start_pos = glm::vec3(-0.5) + increment * 0.5f;
            glm::vec3 current_pos = start_pos;
            //don't forget to put this in constructor
            localToWorld = glm::translate(glm::mat4(1.0f), position) *
                glm::scale(glm::mat4(1.0f), glm::vec3(terrain_scale_factor));
            for (int z = 0; z < num_cubes_xyz; z++) {
                for (int x = 0; x < num_cubes_xyz; x++) {
                    int z_remap = glm::mix(0, height, current_pos.z + 0.5f);
                    int x_remap = glm::mix(0, width, current_pos.x + 0.5f);
                    int alpha = int(*(data + z_remap * width + x_remap * 1));
                    int k = glm::mix(0, num_cubes_xyz, static_cast<float>(alpha) / static_cast<float>(255));
                    for (int y = 0; y < num_cubes_xyz; y++) {
                        if (y < k) {
                            glm::vec3 world_pos = localToWorld * glm::vec4(current_pos, 1.0f);
                            //TODO: delete pointers when finished to avoid memory leaks
                            terrain[x][y][z] = new WIP_Polygon::Node{ world_pos, cube_scale_factor * 0.5f };
                            WIP_Polygon::Rigidbody* rb = new WIP_Polygon::Rigidbody{ glm::vec3(cube_scale_factor), world_pos, std::numeric_limits<float>::infinity(), new BoxCollider(glm::vec3(cube_scale_factor), world_pos, glm::vec3(0.0f, 0.0f, 0.0f)) };
                            rb->mesh_renderer = new WIP_Polygon::MeshRenderer(&WIP_Polygon::RenderShapes::cube, &WIP_Polygon::Shaders::lightingShader, &WIP_Polygon::Textures::sandstone_brick_diffuse.first, rb);
                            rb->mesh_renderer->SetupMesh();
                            WIP_Polygon::AABB* aabb = new WIP_Polygon::AABB{ glm::vec3(cube_scale_factor * 0.5f), world_pos, rb };
                            aabb->name = "aabb-" + std::to_string(x) + "-" + std::to_string(y) + "-" + std::to_string(z);
                            aabb->pNextObject = terrain[x][y][z]->pObjList;
                            terrain[x][y][z]->pObjList = aabb;
                            /*terrain[x][y][z] = new WIP_Polygon::Rigidbody{ glm::vec3(cube_scale_factor), world_pos, std::numeric_limits<float>::infinity(), new BoxCollider(glm::vec3(cube_scale_factor), world_pos, glm::vec3(0.0f, 0.0f, 0.0f)) };
                            terrain[x][y][z]->mesh_renderer = new WIP_Polygon::MeshRenderer(&WIP_Polygon::RenderShapes::cube, &WIP_Polygon::Shaders::lightingShader, &WIP_Polygon::Textures::sandstone_brick_diffuse.first, terrain[x][y][z]);
                            terrain[x][y][z]->mesh_renderer->SetupMesh();*/
                            current_pos = glm::vec3(current_pos.x, current_pos.y + increment.y, current_pos.z);
                        }
                        else {
                            terrain[x][y][z] = nullptr;
                        }
                    }
                    current_pos = glm::vec3(current_pos.x + increment.x, start_pos.y, current_pos.z);
                }
                current_pos = glm::vec3(start_pos.x, start_pos.y, current_pos.z + increment.z);
            }
        }
        stbi_image_free(data);
    }

    int TerrainVolume::remap(float a0, float a1, float b0, float b1) {
        return glm::mix(a0, a1, (b0 / b1));
    }

    void TerrainVolume::renderTerrain() {
        for (int z = 0; z < num_cubes_xyz; z++) {
            for (int x = 0; x < num_cubes_xyz; x++) {
                for (int y = 0; y < num_cubes_xyz; y++) {
                    //gonna have to go through each object in every cell
                    if (terrain[x][y][z] == nullptr /*|| terrain[x][y][z]->mesh_renderer == nullptr*/) {
                        continue;
                    }
                    else {
                        //terrain[x][y][z]->mesh_renderer->DrawMesh();
                        if (terrain[x][y][z]->pObjList == nullptr) { std::cout << "NULLPTR" << "\n"; }
                        for (AABB* a = terrain[x][y][z]->pObjList; a; a = a->pNextObject) {
                            if (a->rigidbody->mesh_renderer == nullptr) {
                                continue;
                            }
                            else {
                                a->rigidbody->mesh_renderer->DrawMesh();
                            }
                        }
                    }
                }
            }
        }
    }
    void TerrainVolume::renderGrid(){
        glm::vec3 offset = glm::vec3(1.0f / static_cast<float>(num_cubes_xyz));
        glm::vec3 start_pos = glm::vec3(-0.5f) + offset * 0.5f;
        glm::vec3 current_pos = start_pos;
        for (int z = 0; z < num_cubes_xyz; z++) {
            for (int x = 0; x < num_cubes_xyz; x++) {
                for (int y = 0; y < num_cubes_xyz; y++) {
                    glm::vec3 world_pos = localToWorld * glm::vec4(current_pos, 1.0f);
                    Debug::DrawDebugCube(world_pos, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(cube_scale_factor), Colors::Yellow, 1.0f);
                    current_pos = glm::vec3(current_pos.x, current_pos.y + offset.y, current_pos.z);
                }
                current_pos = glm::vec3(current_pos.x + offset.x, start_pos.y, current_pos.z);
            }
            current_pos = glm::vec3(start_pos.x, start_pos.y, current_pos.z + offset.z);
        }
    }
    //part of the insertion step may need to be removal from previous cell
    void TerrainVolume::insertObject(AABB* _pObject) {
        /*glm::vec3 local_pos = _pObject->center - position;
        glm::vec3 grid_pos = TerrainVolume::GetClosestGridCellCenterPosition(local_pos, x, y, z);
        glm::vec3 cell_local_pos = local_pos - grid_pos;
        int x_size = _pObject->radius.x - (cube_scale_factor - glm::abs(cell_local_pos.x)) + 1;
        int y_size = _pObject->radius.y - (cube_scale_factor - glm::abs(cell_local_pos.y)) + 1;
        int z_size = _pObject->radius.z - (cube_scale_factor - glm::abs(cell_local_pos.z)) + 1;
        int min_corner_x = glm::clamp(x - x_size, 0, num_cubes_xyz - 1);
        int min_corner_y = glm::clamp(y - y_size, 0, num_cubes_xyz - 1);
        int min_corner_z = glm::clamp(z - z_size, 0, num_cubes_xyz - 1);
        Debug::DrawDebugCube(grid_pos + position, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(cube_scale_factor), Colors::Red, 10.0f);*/
        glm::vec3 local_pos = glm::inverse(localToWorld) * glm::vec4(_pObject->MinCorner(), 1.0f);
        int x{};
        int y{};
        int z{};
        GetTerrainIndices(local_pos, x, y, z);
        if (terrain[x][y][z] != nullptr) {           
            _pObject->pNextObject = terrain[x][y][z]->pObjList;
            terrain[x][y][z]->pObjList = _pObject;
        }
        else {
            //if the node is blank, create new node. node position will need to be gotten via GetGridCellCenterPositionFromTerrainIndices
            glm::vec3 pos = TerrainVolume::GetGridCellCenterPositionFromTerrainIndices(x, y, z);
            terrain[x][y][z] = new WIP_Polygon::Node{ pos, cube_scale_factor * 0.5f};
            terrain[x][y][z]->pObjList = _pObject;
        }
        _pObject->pCurrentNode = terrain[x][y][z];
    }
    void TerrainVolume::removeObject(AABB* _pObject) {
        if (!_pObject->pCurrentNode) { return; }
        AABB* p = _pObject->pCurrentNode->pObjList;
        if (p == _pObject) {
            _pObject->pCurrentNode->pObjList = p->pNextObject;
            p->pNextObject = nullptr;
            if (_pObject->pCurrentNode->pObjList == nullptr) { _pObject->pCurrentNode = nullptr; }
            return;
        }
        while (p) {
            std::cout << "2" << "\n";
            AABB* q = p;
            p = p->pNextObject;
            if (p == _pObject) {
                q->pNextObject = p->pNextObject;
                if (_pObject->pCurrentNode->pObjList == nullptr) { _pObject->pCurrentNode = nullptr; }
                return;
            }
        }
        //use this to dynamically figure out, based off position in grid, current node and remove aabb from it
        /*int x{};
        int y{};
        int z{};
        glm::vec3 local_pos = glm::inverse(localToWorld) * glm::vec4(_pObject->MinCorner(), 1.0f);
        TerrainVolume::GetTerrainIndices(local_pos, x, y, z);
        if (terrain[x][y][z] == nullptr) { return; }
        AABB* p = terrain[x][y][z]->pObjList; 
        
        if (p == _pObject) {
            terrain[x][y][z]->pObjList = p->pNextObject;
            p->pNextObject = nullptr;
            if (terrain[x][y][z]->pObjList == nullptr) { terrain[x][y][z] = nullptr; }
            return;
        }
        while (p) {
            std::cout << "2" << "\n";
            AABB* q = p;
            p = p->pNextObject;
            if (p == _pObject) {
                q->pNextObject = p->pNextObject;
                if (terrain[x][y][z]->pObjList == nullptr) { terrain[x][y][z] = nullptr; }
                return;
            }
        }*/
    }
    glm::vec3 TerrainVolume::GetClosestGridCellCenterPosition(glm::vec3 local_pos, int& x, int& y, int& z) {
        x = glm::clamp(local_pos.x, -terrain_scale_factor * 0.5f, terrain_scale_factor * 0.5f) + terrain_scale_factor * 0.5f;
        y = glm::clamp(local_pos.y, -terrain_scale_factor * 0.5f, terrain_scale_factor * 0.5f) + terrain_scale_factor * 0.5f;
        z = glm::clamp(local_pos.z, -terrain_scale_factor * 0.5f, terrain_scale_factor * 0.5f) + terrain_scale_factor * 0.5f;
        glm::vec3 grid_pos = glm::vec3(
            static_cast<float>(x) - terrain_scale_factor * 0.5f + cube_scale_factor * 0.5f,
            static_cast<float>(y) - terrain_scale_factor * 0.5f + cube_scale_factor * 0.5f,
            static_cast<float>(z) - terrain_scale_factor * 0.5f + cube_scale_factor * 0.5f
        );
        return grid_pos;
    }

    void TerrainVolume::GetTerrainIndices(glm::vec3 local_pos, int& x, int& y, int& z) {
        //glm::vec3 cell_size = 1.0f / glm::vec3(static_cast<float>(num_cubes_xyz));
        glm::vec3 grid_pos = (local_pos + 0.5f) * glm::vec3(static_cast<float>(num_cubes_xyz));/// cell_size;
        x = glm::clamp(grid_pos.x, 0.0f, static_cast<float>(num_cubes_xyz - 1));
        y = glm::clamp(grid_pos.y, 0.0f, static_cast<float>(num_cubes_xyz - 1));
        z = glm::clamp(grid_pos.z, 0.0f, static_cast<float>(num_cubes_xyz - 1));
    }
    glm::vec3 TerrainVolume::GetGridCellCenterPositionFromTerrainIndices(int x, int y, int z) {
        float x_pos = -0.5f + (2.0f * x + 1.0f) / (2.0f * num_cubes_xyz);
        float y_pos = -0.5f + (2.0f * y + 1.0f) / (2.0f * num_cubes_xyz);
        float z_pos = -0.5f + (2.0f * z + 1.0f) / (2.0f * num_cubes_xyz);
        return localToWorld * glm::vec4(x_pos, y_pos, z_pos, 1.0f);
    }
    std::vector<Rigidbody*> TerrainVolume::GetCollisionCells(AABB* a, std::vector < std::pair<WIP_Polygon::AABB*, WIP_Polygon::AABB*>>& collision_pairs) {
        int min_index_x{};
        int max_index_x{};
        int min_index_y{};
        int max_index_y{};
        int min_index_z{};
        int max_index_z{};
        glm::vec3 min_corner = glm::inverse(localToWorld) * glm::vec4(a->center - a->radius, 1.0f);
        glm::vec3 max_corner = glm::inverse(localToWorld) * glm::vec4(a->center + a->radius, 1.0f);
        TerrainVolume::GetTerrainIndices(min_corner, min_index_x, min_index_y, min_index_z);
        TerrainVolume::GetTerrainIndices(max_corner, max_index_x, max_index_y, max_index_z);
        std::vector<Rigidbody*>rbs_to_check{};
        collision_pairs.clear();//this won't delete the pointers, only clears the storage
        //std::vector < std::pair<WIP_Polygon::AABB*, WIP_Polygon::AABB*>> collision_pairs{};
        for (int z = min_index_z; z <= max_index_z; z++) {
            for (int x = min_index_x; x <= max_index_x; x++) {
                for (int y = min_index_y; y <= max_index_y; y++) {
                    if (TerrainVolume::terrain[x][y][z] != nullptr) {
                        //rbs_to_check.push_back(TerrainVolume::terrain[x][y][z]);
                        for (AABB* aabb = terrain[x][y][z]->pObjList; aabb; aabb = aabb->pNextObject) {
                            if (aabb == a) { continue; }
                            rbs_to_check.push_back(aabb->rigidbody);
                            collision_pairs.push_back(std::pair<WIP_Polygon::AABB*, WIP_Polygon::AABB*>(a, aabb));
                        }
                    }
                }
            }
        }
        return rbs_to_check;
    }
    void TerrainVolume::BuildGrid(){
        unsigned int textureID;
        int width, height, nrChannels;
        unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
        if (data) {
            glm::vec3 increment = glm::vec3(1.0f / static_cast<float>(num_cubes_xyz));
            glm::vec3 start_pos = glm::vec3(-0.5) + increment * 0.5f;
            glm::vec3 current_pos = start_pos;
            //don't forget to put this in constructor
            localToWorld = glm::translate(glm::mat4(1.0f), position) *
                glm::scale(glm::mat4(1.0f), glm::vec3(terrain_scale_factor));
            for (int z = 0; z < num_cubes_xyz; z++) {
                for (int x = 0; x < num_cubes_xyz; x++) {
                    int z_remap = glm::mix(0, height, current_pos.z + 0.5f);
                    int x_remap = glm::mix(0, width, current_pos.x + 0.5f);
                    int alpha = int(*(data + z_remap * width + x_remap * 1));
                    int k = glm::mix(0, num_cubes_xyz, static_cast<float>(alpha) / static_cast<float>(255));
                    for (int y = 0; y < num_cubes_xyz; y++) {
                        if (y < k) {
                            glm::vec3 world_pos = localToWorld * glm::vec4(current_pos, 1.0f);
                            //TODO: delete pointers when finished to avoid memory leaks
                            terrain[x][y][z] = new WIP_Polygon::Node{ world_pos, cube_scale_factor * 0.5f };
                            WIP_Polygon::Rigidbody* rb = new WIP_Polygon::Rigidbody{ glm::vec3(cube_scale_factor), world_pos, std::numeric_limits<float>::infinity(), new BoxCollider(glm::vec3(cube_scale_factor), world_pos, glm::vec3(0.0f, 0.0f, 0.0f)) };
                            rb->mesh_renderer = new WIP_Polygon::MeshRenderer(&WIP_Polygon::RenderShapes::cube, &WIP_Polygon::Shaders::lightingShader, &WIP_Polygon::Textures::sandstone_brick_diffuse.first, rb);
                            rb->mesh_renderer->SetupMesh();
                            WIP_Polygon::AABB* aabb = new WIP_Polygon::AABB{ glm::vec3(cube_scale_factor * 0.5f), world_pos, rb };
                            aabb->name = "aabb-" + std::to_string(x) + "-" + std::to_string(y) + "-" + std::to_string(z);
                            aabb->pNextObject = terrain[x][y][z]->pObjList;
                            terrain[x][y][z]->pObjList = aabb;
                            current_pos = glm::vec3(current_pos.x, current_pos.y + increment.y, current_pos.z);
                        }
                        else {
                            terrain[x][y][z] = nullptr;
                        }

                    }
                    current_pos = glm::vec3(current_pos.x + increment.x, start_pos.y, current_pos.z);
                }
                current_pos = glm::vec3(start_pos.x, start_pos.y, current_pos.z + increment.z);
            }
        }
        stbi_image_free(data);

    }
    void TerrainVolume::RenderGridMeshes() {
        for (int z = 0; z < num_cubes_xyz; z++) {
            for (int x = 0; x < num_cubes_xyz; x++) {
                for (int y = 0; y < num_cubes_xyz; y++) {
                    //gonna have to go through each object in every cell
                    if (terrain[x][y][z] == nullptr ) {
                        continue;
                    }
                    else {
                        //terrain[x][y][z]->mesh_renderer->DrawMesh();
                        //i am currently setting terrain[x][y][z] to nullptr if pObjList for that node is nullptr. i am doing this in the
                        //rendermesh method of this class because i don't know how to set terrain[x][y][z] to nullptr from  pCurrentNode.
                        if (terrain[x][y][z]->pObjList == nullptr) {  terrain[x][y][z] = nullptr;  /*std::cout << "NULLPTR" << "\n";*/ continue; }
                        for (AABB* a = terrain[x][y][z]->pObjList; a; a = a->pNextObject) {
                            if (a->rigidbody->mesh_renderer == nullptr) {
                                continue;
                            }
                            else {
                                a->rigidbody->mesh_renderer->DrawMesh();
                            }
                        }
                    }
                }
            }
        }
    }

    void TerrainVolume::RenderGridLines() {
        glm::vec3 offset = glm::vec3(1.0f / static_cast<float>(num_cubes_xyz));
        glm::vec3 start_pos = glm::vec3(-0.5f) + offset * 0.5f;
        glm::vec3 current_pos = start_pos;
        for (int z = 0; z < num_cubes_xyz; z++) {
            for (int x = 0; x < num_cubes_xyz; x++) {
                for (int y = 0; y < num_cubes_xyz; y++) {
                    glm::vec3 world_pos = localToWorld * glm::vec4(current_pos, 1.0f);
                    Debug::DrawDebugCube(world_pos, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(cube_scale_factor), Colors::Yellow, 1.0f);
                    current_pos = glm::vec3(current_pos.x, current_pos.y + offset.y, current_pos.z);
                }
                current_pos = glm::vec3(current_pos.x + offset.x, start_pos.y, current_pos.z);
            }
            current_pos = glm::vec3(start_pos.x, start_pos.y, current_pos.z + offset.z);
        }
    }

    void TerrainVolume::InsertObject(AABB* _pObject) {
        //remove it first to avoid multiple indexing of same object in nodes
        RemoveObject(_pObject);
        glm::vec3 local_pos = glm::inverse(localToWorld) * glm::vec4(_pObject->MinCorner(), 1.0f);
        int x{};
        int y{};
        int z{};
        GetTerrainIndices(local_pos, x, y, z);
        if (terrain[x][y][z] != nullptr) {
            _pObject->pNextObject = terrain[x][y][z]->pObjList;
            terrain[x][y][z]->pObjList = _pObject;
        }
        else {
            //if the node is blank, create new node. node position will need to be gotten via GetGridCellCenterPositionFromTerrainIndices
            glm::vec3 pos = TerrainVolume::GetGridCellCenterPositionFromTerrainIndices(x, y, z);
            terrain[x][y][z] = new WIP_Polygon::Node{ pos, cube_scale_factor * 0.5f };
            terrain[x][y][z]->pObjList = _pObject;
        }
        _pObject->pCurrentNode = terrain[x][y][z];

    }
    void TerrainVolume::RemoveObject(AABB* _pObject) {
        if (!_pObject->pCurrentNode) { return; }
        AABB* p = _pObject->pCurrentNode->pObjList;
        if (p == _pObject) {
            _pObject->pCurrentNode->pObjList = p->pNextObject;
            p->pNextObject = nullptr;
            if (_pObject->pCurrentNode->pObjList == nullptr) { 
                //i am currently setting terrain[x][y][z] to nullptr if pObjList for that node is nullptr. i am doing this in the
                //rendermesh method of this class because i don't know how to set terrain[x][y][z] to nullptr from  pCurrentNode.
                _pObject->pCurrentNode = nullptr; 
            }
            return;
        }
        while (p) {
            std::cout << "2" << "\n";
            AABB* q = p;
            p = p->pNextObject;
            if (p == _pObject) {
                q->pNextObject = p->pNextObject;
                if (_pObject->pCurrentNode->pObjList == nullptr) { _pObject->pCurrentNode = nullptr; }
                return;
            }
        }
    }
    void TerrainVolume::GetCollisionPairs(std::vector < std::pair<WIP_Polygon::AABB*, WIP_Polygon::AABB*>>& collision_pairs) {
        for (int z = 0; z < num_cubes_xyz; z++) {
            for (int x = 0; x < num_cubes_xyz; x++) {
                for (int y = 0; y < num_cubes_xyz; y++) {
                    if (terrain[x][y][z] == nullptr) {
                        continue;
                    }
                    else {
                        for (AABB* a = terrain[x][y][z]->pObjList; a; a = a->pNextObject) {
                            if (a->rigidbody->is_static == true) {
                                continue;
                            }
                            else {
                                int min_index_x{};
                                int max_index_x{};
                                int min_index_y{};
                                int max_index_y{};
                                int min_index_z{};
                                int max_index_z{};
                                glm::vec3 min_corner = glm::inverse(localToWorld) * glm::vec4(a->center - a->radius, 1.0f);
                                glm::vec3 max_corner = glm::inverse(localToWorld) * glm::vec4(a->center + a->radius, 1.0f);
                                TerrainVolume::GetTerrainIndices(min_corner, min_index_x, min_index_y, min_index_z);
                                TerrainVolume::GetTerrainIndices(max_corner, max_index_x, max_index_y, max_index_z);
                                collision_pairs.clear();//this won't delete the pointers, only clears the storage
                                for (int z = min_index_z; z <= max_index_z; z++) {
                                    for (int x = min_index_x; x <= max_index_x; x++) {
                                        for (int y = min_index_y; y <= max_index_y; y++) {
                                            if (TerrainVolume::terrain[x][y][z] != nullptr) {
                                                for (AABB* aabb = terrain[x][y][z]->pObjList; aabb; aabb = aabb->pNextObject) {
                                                    if (aabb == a) { continue; }
                                                    collision_pairs.push_back(std::pair<WIP_Polygon::AABB*, WIP_Polygon::AABB*>(a, aabb));
                                                }
                                            }
                                        }
                                    }
                                }

                            }
                        }
                    }

                }
            }
        }
    }
}