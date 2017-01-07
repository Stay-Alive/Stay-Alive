#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GLFW/glfw3.h>
#include "../config.hpp"
#include "EntityRenderer.hpp"

using namespace std;
EntityRenderer::EntityRenderer(glm::mat4& projectionMatrix)
{
    shader.Use();
    shader.LoadProjectionMatrix(projectionMatrix);
    glUseProgram(0);
}

EntityRenderer::~EntityRenderer()
{

}

void EntityRenderer::BindTexturedModel(TexturedModel texturedModel)
{
    RawModel* model = texturedModel.GetRawModel();
    glBindVertexArray(model->GetVaoID());
    GLuint i;
    for (i = 0; i < 3; i++)
    {
        glEnableVertexAttribArray(i);
    }
    // load status from texture
    ModelTexture texture = texturedModel.GetTexture();
    // disable cull face due to transparency
    if (texture.GetHasTransparency())
    {
        glDisable(GL_CULL_FACE);
    }
    // use the standard up normal or not
    shader.LoadUseUpNormal(texture.GetUseUpNormal());
    // load shineness
    shader.LoadShineVariables(texture.GetShineDamper(), texture.GetShine());
    // bind texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.GetTextureID());
}

void EntityRenderer::UnbindTexturedModel()
{
    // reenable culling face
    glEnable(GL_CULL_FACE);
    // discard attributes
    GLuint i;
    for (i = 0; i < 3; i++)
    {
        glDisableVertexAttribArray(i);
    }
    glBindVertexArray(0);
}

void EntityRenderer::Render(TmEntityMap& entities, glm::vec3 cameraPos)
{
    multimap<GLfloat, Entity> transparentEntities;
    GLfloat distance;
    // traverse the textured model-entity map
    for (auto &pair: entities)
    {
        // pair.first: key
        if (true == pair.first.GetBlendAlpha())
        {
            // pair.second: value
            for (Entity& tmpEntity: pair.second)
            {
                // ordered by distance
                distance = glm::length(cameraPos - tmpEntity.GetPosition());
                transparentEntities.insert(make_pair(distance, tmpEntity));
            }
            continue;
        }
        // models that are not transparency
        BindTexturedModel(pair.first);
        for (Entity& tmpEntity: pair.second)
        {
            RenderEntity(tmpEntity);
        }
        UnbindTexturedModel();
    }
}

void EntityRenderer::RenderEntity(Entity& entity)
{
    glm::vec3 position(entity.GetPosition());
    glm::mat4 transMatrix = glm::translate(position);  // generate translation matrix
    glm::vec3 rotation(entity.GetRotation());
	glm::mat4 rotMatrix =
		glm::rotate(rotation.z, glm::vec3(0, 0, 1)) *
		glm::rotate(rotation.y, glm::vec3(0, 1, 0)) *
		glm::rotate(rotation.x, glm::vec3(1, 0, 0));
	// Create scale matrix
	glm::mat4 scaleMatrix = glm::scale(entity.GetScale());

    shader.LoadTransformMatrix(transMatrix * rotMatrix * scaleMatrix);

    glDrawElements(GL_TRIANGLES, entity.GetModel().GetRawModel()->GetVerticesNum(), GL_UNSIGNED_INT, 0);  // 0 indicates the buffer offset in indices buffer object
}
