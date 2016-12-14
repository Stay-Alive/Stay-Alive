#include <iostream>
#include <cassert>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "../config.hpp"
#include "Loader.hpp"

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
    int indicesCount = indices.size();
    GLuint vaoID = CreateVAO();
    BindIndicesBuffer(&indices[0], indicesCount);
    StoreDataInAttributeList(0, 3, &vertices[0], vertices.size() * sizeof(glm::vec3));
    StoreDataInAttributeList(1, 3, &textures[0], textures.size() * sizeof(glm::vec3));
    StoreDataInAttributeList(2, 3, &normals[0], normals.size() * sizeof(glm::vec3));
    glBindVertexArray(0);
    return RawModel(vaoID, indicesCount);
}

GLuint Loader::LoadTexture(const string& fileName, bool repeat)
{
    GLuint textureID;
    int width, height, componentsCount;
    string completeFileName = TEXTURES_DIR + fileName + ".png";
    stbi_uc *data = stbi_load(completeFileName.c_str(), &width, &height, &componentsCount, 4); // 4 components per pixel
    if (NULL == data)
    {
        cerr << "Failed to load texture image: "  + fileName << endl;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // minifying textures, linear filtering
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // magnifying textures

    // repeating texture for terrain
    if (!repeat)
    {
        // clamp textures to the edge
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    // give the image to openGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    textures.push_back(textureID);
    stbi_image_free(data);
    return textureID;
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
    GLuint vboID;
    glGenBuffers(1, &vboID);
    vbos.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    glVertexAttribPointer(attribNumber, attribSize, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Loader::BindIndicesBuffer(int* indices, int& count)
{
    GLuint vboID;
    glGenBuffers(1, &vboID);
    vbos.push_back(vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);  // @NOTE indexed vbo
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * count, indices, GL_STATIC_DRAW);
    // GL_STATIC_DRAW: The data store contents will be modified once and used many times as the source for GL drawing commands.
}
