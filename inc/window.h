#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <functional>

class Window {
    public:
        ~Window();
        void makeContextCurrent();
        void redraw();
        bool isAboutToClose();
        void onResize(std::function<void(int, int)> callback);
        static Window * create(int width, 
                int height, const std::string & title);
    private:
        GLFWwindow * m_windowHandle;
        int m_width;
        int m_height;
        std::string m_title;
        std::function<void(int, int)> m_onResizeCallback;

        Window(GLFWwindow * windowHandle);
        Window(const Window &);
        Window & operator=(const Window &);
        void windowResized(int width, int height);

        static std::unordered_map<GLFWwindow *, Window *> windows;
        static void onWindowResizeCallback(GLFWwindow * windowHandle, 
                int w, int h);
};


#endif /* end of include guard: WINDOW_H */
