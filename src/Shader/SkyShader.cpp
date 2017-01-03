#include "SkyShader.hpp"
#include "../config.hpp"

SkyShader::SkyShader(): Shader("sky")
{
    BindAttributes();
    GetUniformLocations();
}

SkyShader::~SkyShader()
{

}

void SkyShader::BindAttributes()
{
    glBindAttribLocation(programID, 0, "position");  // @NOTE layout in shader file
    glBindAttribLocation(programID, 1, "uv");
}

void SkyShader::GetUniformLocations()
{
  matrixLoc = glGetUniformLocation(programID, "matrix");
  samplerLoc = glGetUniformLocation(programID, "textureSampler");
  timerLoc = glGetUniformLocation(programID, "timer");
}

void SkyShader::LoadMatrix(const glm::mat4& matrix)
{
    glUniformMatrix4fv(matrixLoc, 1, false, &matrix[0][0]);
}

void SkyShader::LoadTimer(double time)
{
  float t=(float)time;
  glUniform1f(timerLoc,t);
}

void SkyShader::LoadSampler(int sampler){
  glUniform1i(samplerLoc, sampler);    //设置变量的值
}
