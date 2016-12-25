#include <vector>
#include "../config.hpp"
#include "Terrain.hpp"

Terrain::Terrain(Loader& loader, ModelTexture texture): x(-0.5 * TERRAIN_SIZE), z(-0.5 * TERRAIN_SIZE), texture(texture), model(GenerateTerrain(loader))
{

}

Terrain::~Terrain()
{

}

RawModel Terrain::GenerateTerrain(Loader& loader)
{
    int count = TERRAIN_VERTEX_COUNT * TERRAIN_VERTEX_COUNT;  // we have a grid
    vector<glm::vec3> vertices(count), normals(count);
    vector<glm::vec2> textures(count);
    vector<int> indices(6 * (TERRAIN_VERTEX_COUNT - 1) * (TERRAIN_VERTEX_COUNT - 1));
    int i, j, vertexPointer = 0;
    glm::vec3 standardNormal = glm::vec3(0, 1, 0);

    for (i = 0; i < TERRAIN_VERTEX_COUNT; i++)
    {
        for (j = 0; j < TERRAIN_VERTEX_COUNT; j++)
        {
            // compute vertices
            vertices[vertexPointer] = glm::vec3(j * 1.0 / (TERRAIN_VERTEX_COUNT - 1) * TERRAIN_SIZE, 0, i * 1.0 / (TERRAIN_VERTEX_COUNT - 1) * TERRAIN_SIZE);
            // compute normals @NOTE this is a plane
            normals[vertexPointer] = standardNormal;
            // textures
            textures[vertexPointer] = glm::vec2(j * 1.0 / (TERRAIN_VERTEX_COUNT - 1), i * 1.0 / (TERRAIN_VERTEX_COUNT - 1));
            // next vertex
            vertexPointer++;
        }
    }

    int pointer = 0;
    int gx, gz;
    int topLeft, bottomLeft, topRight, bottomRight;
    for (gz = 0; gz < TERRAIN_VERTEX_COUNT - 1; gz++)
    {
        for (gx = 0; gx < TERRAIN_VERTEX_COUNT - 1; gx++)
        {
            topLeft = (gz * TERRAIN_VERTEX_COUNT) + gx;
            topRight = topLeft + 1;
            bottomLeft = ((gz + 1) * TERRAIN_VERTEX_COUNT) + gx;
            bottomRight = bottomLeft + 1;
            // note that one grid needs two triangle
            indices[pointer++] = topLeft;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = topRight;
            indices[pointer++] = topRight;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = bottomRight;
        }
    }
    return loader.Load2VAO(vertices, textures, normals, indices);
}
