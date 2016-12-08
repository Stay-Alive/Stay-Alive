#ifndef LOADER_H
#define LOADER_H
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <iostream>
#include <vector>

using namespace std;

class Loader
{
public:
    Loader();
    ~Loader();
private:
    vector<GLuint> vaos;
    vector<GLuint> vbos;
    vector<GLuint> textures;
    GLuint CreateVAO();  // create vetex array object
    
};

#endif
