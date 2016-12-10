#include <iostream>
#include <cassert>
#define STB_IMAGE_IMPLEMENTATION
#include "Loader.hpp"
#include "stb_image.h"

using namespace std;

Loader::Loader()
{
    vaos.clear();
    vbos.clear();
    textures.clear();
}

Loader::~Loader()
{
    // delete all OpenGL variables
    while (vbos.size() > 0)
    {
        // delete one buffer at a time
		glDeleteBuffers(1, &vbos.back());
        vbos.pop_back();
    }

    while (vaos.size() > 0)
    {
        // delete one array at a time
		glDeleteVertexArrays(1, &vaos.back());
        vaos.pop_back();
    }

	while (textures.size() > 0)
	{
        // delete one texture at a time
		glDeleteTextures(1, &textures.back());
		textures.pop_back();
	}
}

RawModel Loader::Load2VAO(vector<glm::vec3> vertices,
    vector<glm::vec2> textures, vector<glm::vec3> normals, vector<int> indices)
{
    GLuint vaoID = CreateVAO();
    //int indices; // @TODO


}

GLuint Loader::LoadTexture(const std::string& fileName, bool repeat)
{

}

GLuint Loader::CreateVAO()  // create vetex array object
{
    GLuint vaoID;
    // generate a new VAO
    glGenVertexArrays(1, &vaoID);
    // save vaoID to our vector
    vaos.push_back(vaoID);
    // bind VAO
    glBindVertexArray(vaoID);
    return vaoID;
}

void Loader::StoreDataInAttributeList(GLuint attribNumber, int attribSize,
    void* data, int dataSize)
{

}

void Loader::BindIndicesBuffer(int* indices, int& count)
{

}
