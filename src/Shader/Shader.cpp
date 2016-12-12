#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include "../config.hpp"
#include "Shader.hpp"

using namespace std;

Shader::Shader(const string& fileName)
{
    // load vertex shader and fragment shader
    vertShaderID = LoadShader(SHADERS_DIR + fileName + ".vert", GL_VERTEX_SHADER);
    fragShaderID = LoadShader(SHADERS_DIR + fileName + ".frag", GL_FRAGMENT_SHADER);

    // link the program
    programID = glCreateProgram();
    glAttachShader(programID, vertShaderID);
    glAttachShader(programID, fragShaderID);
    glLinkProgram(programID);

    // check the program
    GLint status;
    GLint logLength;
    glGetProgramiv(programID, GL_LINK_STATUS, &status);
    if (GL_FALSE == status)
    {
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);
        GLchar *errorMsg = new GLchar[logLength];
        glGetProgramInfoLog(programID, logLength, NULL, errorMsg);
        cerr << "Cannot validate program " << fileName << endl << errorMsg << endl;
        delete[] errorMsg;
    }
}

Shader::~Shader()
{
    // unuse program
    glUseProgram(0);
    // detach shaders from program
    glDetachShader(programID, vertShaderID);
    glDetachShader(programID, fragShaderID);
    // delte shaders
    glDeleteShader(vertShaderID);
    glDeleteShader(fragShaderID);
    glDeleteProgram(programID);
}

GLuint Shader::LoadShader(const string& fileName, GLenum shaderType)
{
    GLuint shaderID = glCreateShader(shaderType);
    ifstream shaderFile(fileName.c_str());
    if (shaderFile.fail())  // failed to open the shader file
    {
        cerr << "Failed to open shader file: " << fileName << endl;
        exit(-1);
    }
    // extrace the content of the file
    stringstream buffer;
    buffer << shaderFile.rdbuf();
    shaderFile.close();
    string shaderSource = buffer.str();

    const char * shaderSourcePointer = shaderSource.c_str();
    //const int shaderSourceLength = shaderSource.length();
    // compile shader
    glShaderSource(shaderID, 1, &shaderSourcePointer, NULL);  // replace the source code in a shader object
    glCompileShader(shaderID);
    // check shader
    GLint status;
    GLint logLength;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
    if (GL_FALSE == status)
    {
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
        GLchar *errorMsg = new GLchar[logLength];
        glGetShaderInfoLog(shaderID, logLength, NULL, errorMsg);
        cerr << "Failed to compile shader file " << fileName << endl << errorMsg << endl;
        delete[] errorMsg;
    }

    return shaderID;
}
