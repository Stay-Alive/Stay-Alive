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
    vertices.clear();
    normals.clear();
}

RawModel Terrain::GenerateTerrain(Loader& loader)
{
    int count = TERRAIN_VERTEX_COUNT * TERRAIN_VERTEX_COUNT;  // we have a grid
    vertices.resize(count);
    normals.resize(count);
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

GLfloat Terrain::GetAltitudeAt(GLfloat xCoord, GLfloat zCoord)
{
    float step = TERRAIN_STEP;
    int row = TERRAIN_VERTEX_COUNT;
    float x = xCoord + 0.5 * TERRAIN_SIZE;  // normalize so that 0 <= x < TERRAIN_SIZE
    float z = zCoord + 0.5 * TERRAIN_SIZE;
    float offX = fmodf(x, step);
    float offZ = fmodf(z, step);
    glm::vec3 p1, p2, p3;
    /*
        --------- x
        |      /|
        |  U  / |
        |    /  |
        |   /   |
        |  /    |
        | /  D  |
        |/      |
        ---------
        z
    */
    if (offX + offZ <= step)  // (x, z) lies in the upper triangle
    {
        p1.x = trunc(x / step);
        p1.z = trunc(z / step);
        p1.y = vertices[(int)p1.z * row + (int)p1.x].y;

        p2.x = trunc(x / step);
        p2.z = trunc(z / step) + 1;
        p2.y = vertices[(int)p2.z * row + (int)p2.x].y;

        p3.x = trunc(x / step) + 1;
        p3.z = trunc(z / step);
        p3.y = vertices[(int)p3.z * row + (int)p3.x].y;
    }
    else  // the second triangle
    {
        p1.x = trunc(x / step) + 1;
        p1.z = trunc(z / step) + 1;
        p1.y = vertices[(int)p1.z * row + (int)p1.x].y;

        p2.x = trunc(x / step) + 1;
        p2.z = trunc(z / step);
        p2.y = vertices[(int)p2.z * row + (int)p2.x].y;

        p3.x = trunc(x / step);
        p3.z = trunc(z / step) + 1;
        p3.y = vertices[(int)p3.z * row + (int)p3.x].y;
    }
    // turn the coordinates into world units
    p1.x *= step;
    p1.z *= step;
    p2.x *= step;
    p2.z *= step;
    p3.x *= step;
    p3.z *= step;
    /*
    solve plane's equation: Ax + By + Cz = D
    normal vector: n = [A, B, C]'
    (p2 - p1) dot n = 0
    (p3 - p1) dot n = 0
    (p2 - p1) cross (p3 - p1) = n
    */
    glm::vec3 normal = glm::cross(p2 - p1, p3 - p1);
    GLfloat A = normal.x, B = normal.y, C = normal.z, D = glm::dot(p1, normal);
    if (0 == B)
    {
        return 0;
    }
    return (D - A * x - C * z) / B;
}
