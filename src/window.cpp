#include "window.h"
#include <algorithm>


std::unordered_map<GLFWwindow *, std::shared_ptr<Window> > Window::windows;

void Window::onWindowResizeCallback(GLFWwindow * windowHandle, int w, int h){
    auto it = windows.find(windowHandle);
    if(it == windows.end()) return;
    std::shared_ptr<Window> wnd = it->second;
    wnd->windowResized(w, h);
}

std::shared_ptr<Window> Window::create(int width, int height, const std::string & title){
    GLFWwindow * windowHandle = glfwCreateWindow(
            width, height, 
            title.c_str(), NULL, NULL);

    if(windowHandle == NULL) return NULL;

    std::shared_ptr<Window> wnd = std::shared_ptr<Window>(new Window(windowHandle));
    windows.insert(std::make_pair(windowHandle, wnd));
    return wnd;
}

Window::Window(GLFWwindow * windowHandle){
    m_windowHandle = windowHandle;
    glfwSetWindowSizeCallback(m_windowHandle, Window::onWindowResizeCallback);
}

Window::~Window(){
}

void Window::makeContextCurrent(){
    glfwMakeContextCurrent(m_windowHandle);
}

void Window::redraw(){
    glfwSwapBuffers(m_windowHandle);
}

bool Window::isAboutToClose(){
    return glfwWindowShouldClose(m_windowHandle);
}

void Window::onResize(std::function<void(int, int)> callback){
    m_onResizeCallback = callback;
}

void Window::windowResized(int width, int height){
    if(m_onResizeCallback){
        m_onResizeCallback(width, height);
    }
}
