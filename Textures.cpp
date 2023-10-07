#include "Textures.h"
#include "glad\glad.h"
#include "glfw3.h"
//#include "stb_image.h"
#include <iostream>
namespace WIP_Polygon {
	const char* Textures::sandstone_brick_diffuse = "C:/OPENGL/textures/sandstone_brick_wall_diffuse.png";
	const char* Textures::pavement_diffuse = "C:/OPENGL/textures/pavement_diffuse.png";
	const char* Textures::rock_cliff_albedo = "C:/OPENGL/textures/Rock_CliffLayered_albedo.png";

	unsigned int Textures::loadTexture(char const* _path) {
        std::cout << _path << "\n";
        unsigned int textureID{};
        glGenTextures(1, &textureID);
        /*int width, height, nrChannels;
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
        stbi_image_free(data);*/
        return textureID;
    }
}