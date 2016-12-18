#include <vector>
#include "../config.hpp"
#include "Terrain.hpp"

Terrain::Terrain(int gridX, int gridZ, Loader& loader, ModelTexture texture): x(gridX * SIZE), z(gridZ * SIZE), texture(texture), model(GenerateTerrain(loader))
{

}

Terrain::~Terrain()
{

}

RawModel Terrain::GenerateTerrain(Loader& loader)
{
    int count = VERTEX_COUNT * VERTEX_COUNT;  // we have a grid
    vector<glm::vec3> vertices(count), normals(count);
    vector<glm::vec2> textures(count);
    vector<int> indices(6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1));
    int i, j, vertexPointer = 0;
    glm::vec3 standardNormal = glm::vec3(0, 1, 0);

    for (i = 0; i < VERTEX_COUNT; i++)
    {
        for (j = 0; j < VERTEX_COUNT; j++)
        {
            // compute vertices
            vertices[vertexPointer] = glm::vec3(j * 1.0 / (VERTEX_COUNT - 1) * SIZE, 0, i * 1.0 / (VERTEX_COUNT - 1) * SIZE);
            // compute normals @NOTE this is a plane
            normals[vertexPointer] = standardNormal;
            // textures
            textures[vertexPointer] = glm::vec2(j * 1.0 / (VERTEX_COUNT - 1), i * 1.0 / (VERTEX_COUNT - 1));
#if 0
            if (i == j)
            {
                cerr << "vertices[" << vertexPointer << "]: " << vertices[vertexPointer].x << ", " << vertices[vertexPointer].y << ", " << vertices[vertexPointer].z << endl;

                cerr << "textures[" << vertexPointer << "]: " << textures[vertexPointer].x << ", " << textures[vertexPointer].y << endl;
            }

#endif
            // next vertex
            vertexPointer++;
        }
    }

    int pointer = 0;
    int gx, gz;
    int topLeft, bottomLeft, topRight, bottomRight;
    for (gz = 0; gz < VERTEX_COUNT - 1; gz++)
    {
        for (gx = 0; gx < VERTEX_COUNT - 1; gx++)
        {
            topLeft = (gz * VERTEX_COUNT) + gx;
            topRight = topLeft + 1;
            bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
            bottomRight = bottomLeft + 1;
            // note that one grid needs two triangle
            indices[pointer++] = topLeft;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = topRight;
            indices[pointer++] = topRight;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = bottomRight;
#if 0
            for (int i = pointer - 6; i < pointer; i++)
            {
                cerr << "indices[" << i << "]: " << indices[i] << endl;
            }
#endif
        }
    }
    return loader.Load2VAO(vertices, textures, normals, indices);
}
