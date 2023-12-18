#include "Terrain_Volume.h"

namespace WIP_Polygon {
	TerrainVolume::TerrainVolume() {}

    TerrainVolume::TerrainVolume(glm::vec3 _position, float _cube_scale_factor) :
        position{ _position }, terrain_scale_factor{ num_cubes_xyz * _cube_scale_factor }, cube_scale_factor{ _cube_scale_factor }, localToWorld {
            glm::translate(glm::mat4(1.0f), _position)*
            glm::scale(glm::mat4(1.0f), glm::vec3(static_cast<float>(terrain_scale_factor)))
        }
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
                    for (int y = 0; y < k; y++) {
                        glm::vec3 world_pos = localToWorld * glm::vec4(current_pos, 1.0f);
                        terrain[x][y][z] = WIP_Polygon::Rigidbody{ glm::vec3(cube_scale_factor), world_pos, std::numeric_limits<float>::infinity(), new BoxCollider(glm::vec3(cube_scale_factor), world_pos, glm::vec3(0.0f, 0.0f, 0.0f)) };
                        terrain[x][y][z].mesh_renderer = new WIP_Polygon::MeshRenderer(&WIP_Polygon::RenderShapes::cube, &WIP_Polygon::Shaders::lightingShader, &WIP_Polygon::Textures::sandstone_brick_diffuse.first, &terrain[x][y][z]);
                        terrain[x][y][z].mesh_renderer->SetupMesh();
                        current_pos = glm::vec3(current_pos.x, current_pos.y + increment.y, current_pos.z);
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
                    if (terrain[x][y][z].mesh_renderer == nullptr) {
                        //std::cout << "mesh null_ptr" << "\n";
                        continue;
                    }
                    else {
                        terrain[x][y][z].mesh_renderer->DrawMesh();
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
    void TerrainVolume::insertObject(AABB* _pObject, int& x, int& y, int& z) {
        glm::vec3 local_pos = _pObject->center - position;
        glm::vec3 grid_pos = TerrainVolume::GetClosestGridCellCenterPosition(local_pos, x, y, z);
        glm::vec3 cell_local_pos = local_pos - grid_pos;
        int x_size = _pObject->radius.x - (cube_scale_factor - glm::abs(cell_local_pos.x)) + 1;
        int y_size = _pObject->radius.y - (cube_scale_factor - glm::abs(cell_local_pos.y)) + 1;
        int z_size = _pObject->radius.z - (cube_scale_factor - glm::abs(cell_local_pos.z)) + 1;
        int min_corner_x = glm::clamp(x - x_size, 0, num_cubes_xyz - 1);
        int min_corner_y = glm::clamp(y - y_size, 0, num_cubes_xyz - 1);
        int min_corner_z = glm::clamp(z - z_size, 0, num_cubes_xyz - 1);


        Debug::DrawDebugCube(grid_pos + position, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(cube_scale_factor), Colors::Red, 10.0f);
    }
    void TerrainVolume::removeObject() {
    
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
}