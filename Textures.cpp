#include "Textures.h"
namespace WIP_Polygon {

    std::pair<unsigned int, const char*> Textures::sandstone_brick_diffuse = 
        std::pair<unsigned int, const char*>(0, "C:/OPENGL/textures/sandstone_brick_wall_diffuse.png");
    std::pair<unsigned int, const char*> Textures::pavement_diffuse =
        std::pair<unsigned int, const char*>(0, "C:/OPENGL/textures/pavement_diffuse.png");
    std::pair<unsigned int, const char*> Textures::rock_cliff_albedo =
        std::pair<unsigned int, const char*>(0, "C:/OPENGL/textures/Rock_CliffLayered_albedo.png");
    std::pair<unsigned int, const char*> Textures::grid_cell_noise_0 =
        std::pair<unsigned int, const char*>(0, "C:/OPENGL/textures/test_texture_20231112171844.8591522.png");
    std::pair<unsigned int, const char*> Textures::grid_cell_noise_1 =
        std::pair<unsigned int, const char*>(0, "C:/OPENGL/textures/test_texture_20231115205904.8954244.png");
    std::vector < std::pair<unsigned int, const char*>*> Textures::textures = {
        &sandstone_brick_diffuse,
        &pavement_diffuse,
        &rock_cliff_albedo,
        &grid_cell_noise_0,
        &grid_cell_noise_1
    };
    void Textures::loadTextures() {
        for (int i = 0; i < Textures::textures.size(); i++) {
            Textures::textures[i]->first = Textures::loadTexture(Textures::textures[i]->second);
        }
    }
	unsigned int Textures::loadTexture(char const* _path) {
        unsigned int textureID{};
        glGenTextures(1, &textureID);
        int width, height, nrChannels;
        unsigned char* data = stbi_load(_path, &width, &height, &nrChannels, 0);
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
    }
}