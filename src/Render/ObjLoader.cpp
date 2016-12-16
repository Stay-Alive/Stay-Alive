#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include "../config.hpp"
#include "ObjLoader.hpp"
#include <glm/glm.hpp>
using namespace std;

const int MAX_LINE_LEN = 256;

RawModel ObjLoader::LoadModel(const string& fileName, Loader& loader)
{
    vector<glm::vec2> textures, tmpTextures;
    vector<glm::vec3> vertices, normals, tmpNormals;
    vector<int> indices;
    string completeFileName = MODELS_DIR + fileName + ".obj";
    ifstream modelFile(completeFileName.c_str());  // open file
    if (modelFile.fail())
    {
        cerr << "Failed to open " << fileName << ".obj" << endl;
        exit(-1);
    }

    string rawLine;
    vector<string> tokens;
    double x, y, z;

    int vertexPointer;
    vector<string> vertexIndices;  // i.e., f 168/7/3 170/8/3 8/9/3, where 168 is the vertex's index, 7 is the index of its texture uv coordinates, and 3 is the index of its normal

    while (!modelFile.eof())  // read-by-line
    {
        getline(modelFile, rawLine);
        tokens.clear();
        Split(rawLine, ' ', tokens);
        if (tokens[0] == "v")  // v for vertex point
        {
            x = std::stod(tokens[1]);
            y = std::stod(tokens[2]);
            z = std::stod(tokens[3]);
            vertices.push_back(glm::vec3(x, y, z));
        }
        else if (tokens[0] == "vt")  // vt for vertex texture coordinates
        {
            x = std::stod(tokens[1]);
            y = 1 - std::stod(tokens[2]);  // @NOTE why we need to subtract it from 1
			tmpTextures.push_back(glm::vec2(x, y));
        }
        else if (tokens[0] == "vn")  // vn for normals
        {
            x = std::stod(tokens[1]);
            y = std::stod(tokens[2]);
            z = std::stod(tokens[3]);
			tmpNormals.push_back(glm::vec3(x, y, z));
        }
        else if (tokens[0] == "f")
        {
            if (0 == indices.size())
            {
                textures.resize(vertices.size() + 1);
                normals.resize(vertices.size() + 1);
            }
            for (int i = 0; i < 3; i++)
            {
                vertexIndices.clear();
                Split(tokens[i + 1], '/', vertexIndices);
                vertexPointer = std::stoi(vertexIndices[0]);
                if (vertexPointer >= (int)vertices.size() + 1)
                {
                    cerr << "Damn it, vector is not large enough!\n vertexPointer: " << vertexPointer << ">= " << vertices.size() << endl;
                    exit(-1);
                }
                indices.push_back(vertexPointer);
                textures[vertexPointer] = tmpTextures[std::stoi(vertexIndices[1])];
                normals[vertexPointer] = tmpNormals[std::stoi(vertexIndices[2])];
            }
        }
    }
    modelFile.close();  // close obj file
	return loader.Load2VAO(vertices, textures, normals, indices);
}

void ObjLoader::Split(const string& str, char delim, vector<string>& tokens)
{
    stringstream ss(str);
    string item;
    while (getline(ss, item, delim))
    {
        tokens.push_back(item);
    }
}
