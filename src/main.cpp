#include <GL/glew.h>
#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <cstddef>
#include <GLFW/glfw3.h>
#include <functional>
#include "app.h"
#include "window.h"


void onResize(GLFWwindow* window, int newWidth, int newHeight) {
}

bool initializeGlew(){
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();

    if(GLEW_OK != glewError){
        std::cerr << "GLEW initialization failed" << std::endl;
        std::cerr << "Error: " << glewGetErrorString(glewError) << std::endl;
        return false;
    } 

    std::cout << "GL_VERSION = " << glGetString(GL_VERSION) << std::endl;
    return true;
}

void onGlfwError(int error, const char* description){
    std::cerr << "Error: " << description << std::endl;
}


int main(int argc, char** argv){
    const int width = 1280;
    const int height = 960;

    if(!glfwInit()) return EXIT_FAILURE;
    glfwSetErrorCallback(onGlfwError);

    std::shared_ptr<Window> window = Window::create(width, height, "opengl-template");

    if(!window){
        glfwTerminate();
        return EXIT_FAILURE;
    }
    window->makeContextCurrent();
    if(!initializeGlew()) return EXIT_FAILURE;

    App app;
    app.init();

    window->onResize([&app](int w, int h){
            app.setViewport(w, h);
    });

    while(!window->isAboutToClose()){
        app.update();
        window->redraw();
        glfwPollEvents();
    }
    app.deinit();
    glfwTerminate();
    return EXIT_SUCCESS;
}
