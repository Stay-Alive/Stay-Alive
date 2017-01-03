#ifndef SKY_RENDERER_H
#define SKY_RENDERER_H

#include <iostream>
#include <vector>
#include "../Shader/SkyShader.hpp"
using namespace std;

class SkyRenderer
{
public:
    SkyRenderer(GLuint TextureID);
    virtual ~SkyRenderer();
    void GenerateBuffer();
    void Render(const double PreciseTime);
private:
    SkyShader shader;
    GLuint textureID;
    GLuint SkyBuffer;
    GLfloat* data;
    GLsizei size;

    void MakeSphere(GLfloat r, GLint detail);
    int _MakeSphere(GLfloat r, GLuint detail,
    GLfloat *a, GLfloat *b, GLfloat *c,
    GLfloat *ta, GLfloat *tb, GLfloat *tc);

    inline void normalize(float *x, float *y, float *z){
      float d = sqrtf((*x) * (*x) + (*y) * (*y) + (*z) * (*z));
      *x /= d; *y /= d; *z /= d;
    };

};

#endif
