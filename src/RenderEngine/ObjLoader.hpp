#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "Loader.hpp"
#include "../Model/RawModel.hpp"

using namespace std;

class ObjLoader
{
public:
    static RawModel LoadModel(const string& fileName, Loader& loader);
};

void Split(const string& str, char delim, vector<string>& tokens);

#endif
