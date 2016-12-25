#ifndef ENTITY_RENDERER_H
#define ENTITY_RENDERER_H

#include <iostream>
#include <vector>
#include <map>
#include "../Model/TexturedModel.hpp"
#include "../Shader/EntityShader.hpp"
#include "../Entity/Entity.hpp"
using namespace std;

struct texturedModelCmp
{
public:
    bool operator()(const TexturedModel& tm1, const TexturedModel& tm2) const
    {
        return (tm1.GetRawModel().GetVaoID() < tm2.GetRawModel().GetVaoID()) || (tm1.GetTexture().GetTextureID() < tm2.GetTexture().GetTextureID());
    }
};

typedef map<TexturedModel, vector<Entity>, texturedModelCmp> TmEntityMap;

class EntityRenderer
{
public:
    EntityRenderer(glm::mat4& projectionMatrix);
    virtual ~EntityRenderer();
    void Render(TmEntityMap& entities, glm::vec3 cameraPos);

    inline EntityShader& GetShader()
    {
        return shader;
    }

private:
    EntityShader shader;
    void BindTexturedModel(TexturedModel texturedModel);
    void UnbindTexturedModel();
    void RenderEntity(Entity& entity);
};

#endif
