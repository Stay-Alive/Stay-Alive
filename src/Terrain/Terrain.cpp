#include <vector>
#include "../config.hpp"
#include "Terrain.hpp"
#include <SDL/SDL_image.h>
#include "../Render/stb_image.h"

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

    //SDL_Surface *image;
    //image = IMG_Load("./textures/heightmap.png");  // @TODO thought we should avoid putting a path here
    //uint8_t *pixels = (uint8_t *)image->pixels;
    //float xScale = ((float)image->w) / (TERRAIN_SIZE - 1);
    //float zScale = ((float)image->h) / (TERRAIN_SIZE - 1);

    int imgWidth, imgHeight, componentsCount;
    string completeFileName("./textures/heightmap.png");
    stbi_uc *pixels = stbi_load(completeFileName.c_str(), &imgWidth, &imgHeight, &componentsCount, 4); // 3 components per pixel
    float xScale = ((float)imgWidth) / (TERRAIN_SIZE - 1);
    float zScale = ((float)imgHeight) / (TERRAIN_SIZE - 1);

    GLfloat xCoord, height, zCoord;
    for (i = 0; i < TERRAIN_VERTEX_COUNT; i++)
    {
        for (j = 0; j < TERRAIN_VERTEX_COUNT; j++)
        {
            xCoord = j * 1.0 / (TERRAIN_VERTEX_COUNT - 1) * TERRAIN_SIZE;
            zCoord = i * 1.0 / (TERRAIN_VERTEX_COUNT - 1) * TERRAIN_SIZE;
            int imgX = (int)truncf(xCoord * xScale);
            int imgY = (int)truncf(zCoord * zScale);
            height = pixels[imgY * imgWidth * 4 + imgX * 4];
            // Normalize height to [-1, 1]
            height = height / 127.5 - 1.0;
            height *= TERRAIN_HEIGHT_SCALE;
            // compute vertices
            vertices[vertexPointer] = glm::vec3(xCoord, height, zCoord);
            // textures
            textures[vertexPointer] = glm::vec2(j * 1.0 / (TERRAIN_VERTEX_COUNT - 1), i * 1.0 / (TERRAIN_VERTEX_COUNT - 1));
            // next vertex
            vertexPointer++;
        }
    }
    stbi_image_free(pixels);

    // compute normals
    vertexPointer = 0;
    for (i = 0; i < TERRAIN_VERTEX_COUNT; i++)
    {
        for (j = 0; j < TERRAIN_VERTEX_COUNT; j++)
        {
            if (0 == i || 0 == j || TERRAIN_VERTEX_COUNT - 1 == i || TERRAIN_VERTEX_COUNT - 1 == j)  // edge, we just set normal = (0, 1, 0)
            {
                normals[vertexPointer] = standardNormal;
                vertexPointer++;
                continue;
            }
            // left, right, up and down points' heights
            GLfloat heightLeft = vertices[i * TERRAIN_VERTEX_COUNT + j - 1].y;
            GLfloat heightRight = vertices[i * TERRAIN_VERTEX_COUNT + j + 1].y;
            GLfloat heightUp = vertices[(i - 1) * TERRAIN_VERTEX_COUNT + j].y;
            GLfloat heightDown = vertices[(i + 1) * TERRAIN_VERTEX_COUNT + j].y;
            // current point's normal
            glm::vec3 currentNormal = glm::vec3(heightLeft - heightRight, 2.0f, heightDown - heightUp);
            // normalize
            normals[vertexPointer] = glm::normalize(currentNormal);

            vertexPointer++;
        }
    }

    // generate indices
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
