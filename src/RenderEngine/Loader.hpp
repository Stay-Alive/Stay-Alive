#ifndef LOADER_H
#define LOADER_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "../Model/RawModel.hpp"

using namespace std;

class Loader
{
public:
    Loader();
    ~Loader();
	RawModel Load2VAO(std::vector<glm::vec3> vertices, std::vector<glm::vec2> textures, std::vector<glm::vec3> normals, std::vector<int> indices);
	GLuint LoadTexture(const std::string& fileName, bool repeat = false);
	inline void UnbindVAO() { glBindVertexArray(0); }
private:
    vector<GLuint> vaos;
    vector<GLuint> vbos;
    vector<GLuint> textures;
    GLuint CreateVAO();  // create vetex array object
	void StoreDataInAttributeList(GLuint attribNumber, int attribSize, void* data, int dataSize);
	void BindIndicesBuffer(int* indices, int& count);

};

#endif
