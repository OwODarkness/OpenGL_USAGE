#include "CommonUtils.h"
#include "stb_image.h"
#include <iostream>


void CommonUtils::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


unsigned int CommonUtils::textureLoader(const std::string& path, const int RGBMODE)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, RGBMODE, width, height, 0, RGBMODE, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << path << ", data load failed" << std::endl;
    }

    stbi_image_free(data);
    return texture;
}

float CommonUtils::Clamp(float value, float min, float max)
{
    if (value > max) {
        return max;
    }
    else if (value < min) {
        return min;
    }
    else {
        return value;
    }
}
