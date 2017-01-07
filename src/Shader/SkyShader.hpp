#ifndef SKY_SHADER_H
#define SKY_SHADER_H

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "Shader.hpp"

class SkyShader: public Shader
{
public:
    SkyShader();
    virtual ~SkyShader();
    virtual void BindAttributes();
    virtual void GetUniformLocations();
    void LoadMatrix(const glm::mat4& matrix);
    void LoadTimer(double time);
    void LoadSampler(int samplerLoc);

    inline GLuint GetsamplerLoc(){
      return samplerLoc;
    }

    inline GLuint GettimerLoc(){
      return timerLoc;
    }

    inline GLuint GetmatrixLoc(){
      return matrixLoc;
    }

private:
    GLuint matrixLoc;
    GLuint samplerLoc;
    GLuint timerLoc;
};

#endif
