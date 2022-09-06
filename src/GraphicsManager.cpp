#include "GraphicsManager.h"


void GraphicsManager::Startup() {
    glfwInit();
    // We'll use sokol_gfx's OpenGL backend
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    const char* p = Default.window_name.c_str();//packs String into const char
    window = glfwCreateWindow(Default.window_width, Default.window_height, p, Default.window_fullscreen ? glfwGetPrimaryMonitor() : 0, 0);
    glfwSetWindowAspectRatio(window, Default.window_width, Default.window_height);
    if (!window)
    {
        std::cerr << "Failed to create a window." << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    delete p;
}


void GraphicsManager::Shutdown() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void GraphicsManager::Draw() {}