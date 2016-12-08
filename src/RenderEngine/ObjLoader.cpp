#include "ObjLoader.hpp"
#include <iostream>
#include <stdio.h>
using namespace std;

RawModel ObjLoader::LoadModel(const string& fileName, Loader& loader)
{
    FILE *modelFile;
    vector<glm::vec2> textures, tempTextures;
    vector<glm::vec3> vertices, normals, tmpNormals;
    vector<int> indices;

    modelFile = fopen(("../../models/" + fileName + ".obj").c_str(), "r");
    if (NULL == modelFile)
    {
        cerr << "Failed to open " << fileName << ".obj" << endl;
        exit(0);
    }

    // @TODO

    fclose(modelFile);
}

void ObjLoader::ProcessVertices()
{

}
