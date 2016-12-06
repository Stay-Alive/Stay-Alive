#ifndef DISPLAY_H
#define DISPLAY_H
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

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
    string title;
    double aspect;
};
#endif
