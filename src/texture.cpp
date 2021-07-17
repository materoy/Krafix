#include <string>
#include <string.h>
#include "texture.h"
#include <iostream>
#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "helpers/RootDir.h"

unsigned int loadTexture(std::string filePath, unsigned int textureUnit)
{
    int width, height, nrChannels;
    const char* strFilePath = const_cast<char*>(filePath.c_str());
    unsigned char* data = stbi_load(
                strcpy((char *) ((std::string) ROOT_DIR).c_str(), strFilePath), &width, &height, &nrChannels, 0);
    if (data)
    {
        unsigned int texture;
        glGenTextures(1, &texture);
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        return texture;
    }
   else
   {
       std::cout << "Failed to get texture image" << std::endl;
       return EXIT_FAILURE;
   }
    
}
