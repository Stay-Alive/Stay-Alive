#ifndef DISPLAY_H
#define DISPLAY_H

#include <GLFW/glfw3.h>
class Display
{
public:
    Display();
    ~Display();
    void Update();
    bool IsWindowClosed();
    double GetAspect();
    void ShowFPS();
private:
    GLFWwindow *window;
    double aspect;
};
#endif
