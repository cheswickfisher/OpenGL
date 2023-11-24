#include "Terrain_Volume.h"

namespace WIP_Polygon {
	TerrainVolume::TerrainVolume() {}

    TerrainVolume::TerrainVolume(glm::vec3 _position, int _scale) :
        position{ _position }, terrain_scale{ _scale }, localToWorld{
            glm::translate(glm::mat4(1.0f), _position)*
            glm::scale(glm::mat4(1.0f), glm::vec3(static_cast<float>(_scale)))
        }
    {}
    void TerrainVolume::loadTerrain(char const* path) {
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
            int center_x = (width / cells_per_row) / 2;
            int center_z = (height / cells_per_row) / 2;
            glm::vec3 increment = glm::vec3(1.0f / static_cast<float>(cells_per_row));
            glm::vec3 cube_scale = glm::vec3(static_cast<float>(terrain_scale) / static_cast<float>(cells_per_row));
            std::cout << cube_scale.x << "\n";
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
                        terrain[x][y][z] = WIP_Polygon::Rigidbody{cube_scale, world_pos, std::numeric_limits<float>::infinity(), new BoxCollider(cube_scale, world_pos, glm::vec3(0.0f, 0.0f, 0.0f))};
                        terrain[x][y][z].mesh_renderer = new WIP_Polygon::MeshRenderer(&WIP_Polygon::RenderShapes::cube, &WIP_Polygon::Shaders::lightingShader, &WIP_Polygon::Textures::rock_cliff_albedo.first, &terrain[x][y][z]);
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

    void TerrainVolume::renderTerrain() {
        for (int z = 0; z < cells_per_row; z++) {
            for (int x = 0; x < cells_per_row; x++) {
                for (int y = 0; y < cells_per_row; y++) {
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
}