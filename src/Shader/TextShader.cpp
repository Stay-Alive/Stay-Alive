#include "TextShader.hpp"

TextShader::TextShader(): Shader("text")
{
    BindAttributes();
    GetUniformLocations();
}

TextShader::~TextShader()
{

}

void TextShader::BindAttributes()
{
    glBindAttribLocation(programID, 0, "position");  // @NOTE layout in shader file
    glBindAttribLocation(programID, 1, "texCoords");
}

void TextShader::GetUniformLocations()
{
    matrixLoc = glGetUniformLocation(programID, "matrix");
}

void TextShader::LoadMatrix(const glm::mat4& matrix)
{
    glUniformMatrix4fv(matrixLoc, 1, false, &matrix[0][0]);
}
