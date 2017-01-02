#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include "../config.hpp"
#include "ObjLoader.hpp"
#include <glm/glm.hpp>
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"
using namespace std;

const int MAX_LINE_LEN = 256;

RawModel ObjLoader::LoadModel(const string& fileName, Loader& loader)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	string completeFileName = MODELS_DIR + fileName + ".obj";
	std::string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, completeFileName.c_str());

	if (!err.empty())
	{ // `err` may contain warning message.
		std::cerr << err << std::endl;
	}

	if (!ret)
	{
		exit(1);
	}

	vector<glm::vec2> textures;
	vector<glm::vec3> vertices, normals;
	vector<int> indices;
    int indexNum = 0;
	// Loop over shapes
	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			size_t fv = shapes[s].mesh.num_face_vertices[f];

			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				float vx = attrib.vertices[3*idx.vertex_index+0];
				float vy = attrib.vertices[3*idx.vertex_index+1];
				float vz = attrib.vertices[3*idx.vertex_index+2];
                vertices.push_back(glm::vec3(vx, vy, vz));
				float nx = attrib.normals[3*idx.normal_index+0];
				float ny = attrib.normals[3*idx.normal_index+1];
				float nz = attrib.normals[3*idx.normal_index+2];
                normals.push_back(glm::vec3(nx, ny, nz));
				float tx = attrib.texcoords[2*idx.texcoord_index+0];
				float ty = attrib.texcoords[2*idx.texcoord_index+1];
                textures.push_back(glm::vec2(tx, 1 - ty));
                indices.push_back(indexNum++);
			}
			index_offset += fv;

			// per-face material
			shapes[s].mesh.material_ids[f];
		}
	}

	return loader.Load2VAO(vertices, textures, normals, indices);
}

/*
RawModel ObjLoader::LoadModel(const string& fileName, Loader& loader)
{
    vector<glm::vec2> textures, tmpTextures;
    vector<glm::vec3> vertices, normals, tmpNormals;  // @TODO vertices vector should be a private member of RawModel
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
                textures.resize(vertices.size());
                normals.resize(vertices.size());
            }
            for (int i = 0; i < 3; i++)
            {
                vertexIndices.clear();
                Split(tokens[i + 1], '/', vertexIndices);
                vertexPointer = std::stoi(vertexIndices[0]) - 1;
                if (vertexPointer >= (int)vertices.size())
                {
                    cerr << "Damn it, vector is not large enough!\n vertexPointer: " << vertexPointer << ">= " << vertices.size() << endl;
                    exit(-1);
                }
                indices.push_back(vertexPointer);
                textures[vertexPointer] = tmpTextures[std::stoi(vertexIndices[1]) - 1];
                normals[vertexPointer] = tmpNormals[std::stoi(vertexIndices[2]) - 1];
            }
        }
    }
    modelFile.close();  // close obj file
    return loader.Load2VAO(vertices, textures, normals, indices);
}
*/

void ObjLoader::Split(const string& str, char delim, vector<string>& tokens)
{
	stringstream ss(str);
	string item;
	while (getline(ss, item, delim))
	{
		tokens.push_back(item);
	}
}
