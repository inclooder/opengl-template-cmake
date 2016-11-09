#ifndef APP_H
#define APP_H

class App {
    public:
        App();
        ~App();
        void init();
        void setViewport(unsigned int width, unsigned int height);
        void deinit();
        void update();
    private:
        App(const App& other) = delete;
        App& operator=(const App&) = delete;
};


#endif /* end of include guard: APP_H */
