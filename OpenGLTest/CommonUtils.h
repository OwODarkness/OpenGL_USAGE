#ifndef COMMONUTILS_H
#define COMMONUTILS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class CommonUtils {
public:
    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    
    static unsigned int textureLoader(const std::string& path, const int RGBMODE);

    static float Clamp(float value, float min, float max);
};


#endif
