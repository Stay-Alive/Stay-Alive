#include <iostream>
#include <vector>
#include <new>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GLFW/glfw3.h>
#include "../config.hpp"
#include "SkyRenderer.hpp"

using namespace std;

SkyRenderer::SkyRenderer(GLuint textureID): textureID(textureID)
{
  GenerateBuffer();//generate VBO
}

SkyRenderer::~SkyRenderer()
{
  glDeleteBuffers(1, &SkyBuffer);
//  delete [] data;
}

void SkyRenderer::Render(const double PreciseTime)
{
//  glDisable(GL_DEPTH_TEST);
  glDepthMask(GL_FALSE);
    glm::vec3 posvector(0.0f,0.0f,0.0f);
    glm::mat4 transMatrix = glm::translate(posvector);
    glm::vec3 rotation(0, 0, 0);
    glm::mat4 rotMatrix =
  		glm::rotate(rotation.z, glm::vec3(0, 0, 1)) *
  		glm::rotate(rotation.y, glm::vec3(0, 1, 0)) *
  		glm::rotate(rotation.x, glm::vec3(1, 0, 0));
    glm::mat4 perspMatrix = glm::perspective(FIELD_OF_VIEW, (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, Z_NEAR, Z_FAR);//znear和zfar的值，fov
    glm::mat4 matrix = perspMatrix * rotMatrix * transMatrix;

//    glClear(GL_DEPTH_BUFFER_BIT);
    shader.Use();
    shader.LoadMatrix(matrix);
    shader.LoadTimer(PreciseTime);


    //generate VAO
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    //Binding
    glBindVertexArray(vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, SkyBuffer);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    const GLuint position = 0, uv = 1, normal = 2;
    glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE,sizeof(GLfloat) * 8, 0);
    glVertexAttribPointer(uv, 2, GL_FLOAT, GL_FALSE,sizeof(GLfloat) * 8, (GLvoid *)(sizeof(GLfloat) * 6));
    glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid *)(sizeof(GLfloat) * 3));

    glEnableVertexAttribArray(position);
    glEnableVertexAttribArray(uv);
    glEnableVertexAttribArray(normal);

    shader.LoadSampler(0);
//    cout << "textureID = " << textureID << endl;

    glDrawArrays(GL_TRIANGLES, 0, SKY_COUNT);

    glDisableVertexAttribArray(position);
    glDisableVertexAttribArray(uv);
    glDisableVertexAttribArray(normal);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glUseProgram(0);  // unuse
    glBindVertexArray(0);
    glDepthMask(GL_TRUE);
    //glEnable(GL_DEPTH_TEST);
}

void SkyRenderer::MakeSphere(GLfloat* data,GLfloat r, GLint detail) {
    // detail, triangles, floats
    // 0, 8, 192
    // 1, 32, 768
    // 2, 128, 3072
    // 3, 512, 12288
    // 4, 2048, 49152
    // 5, 8192, 196608
    // 6, 32768, 786432
    // 7, 131072, 3145728
    static GLint indices[8][3] = {
        {4, 3, 0}, {1, 4, 0},
        {3, 4, 5}, {4, 1, 5},
        {0, 3, 2}, {0, 2, 1},
        {5, 2, 3}, {5, 1, 2}
    };
    static GLfloat positions[6][3] = {
        { 0, 0,-1}, { 1, 0, 0},
        { 0,-1, 0}, {-1, 0, 0},
        { 0, 1, 0}, { 0, 0, 1}
    };
    static GLfloat uvs[6][3] = {
        {0, 0.5}, {0, 0.5},
        {0, 0}, {0, 0.5},
        {0, 1}, {0, 0.5}
    };
    int total = 0;
    for (int i = 0; i < 8; i++) {
        int n = _MakeSphere(
            data, r, detail,
            positions[indices[i][0]],
            positions[indices[i][1]],
            positions[indices[i][2]],
            uvs[indices[i][0]],
            uvs[indices[i][1]],
            uvs[indices[i][2]]);
        total += n; data += n * 24;
    }
}

int SkyRenderer::_MakeSphere(
GLfloat *data, GLfloat r, GLuint detail,
GLfloat *a, GLfloat *b, GLfloat *c,
GLfloat *ta, GLfloat *tb, GLfloat *tc)
{
  if (detail == 0) {
      float *d = data;
      *(d++) = a[0] * r; *(d++) = a[1] * r; *(d++) = a[2] * r;
      *(d++) = a[0]; *(d++) = a[1]; *(d++) = a[2];
      *(d++) = ta[0]; *(d++) = ta[1];
      *(d++) = b[0] * r; *(d++) = b[1] * r; *(d++) = b[2] * r;
      *(d++) = b[0]; *(d++) = b[1]; *(d++) = b[2];
      *(d++) = tb[0]; *(d++) = tb[1];
      *(d++) = c[0] * r; *(d++) = c[1] * r; *(d++) = c[2] * r;
      *(d++) = c[0]; *(d++) = c[1]; *(d++) = c[2];
      *(d++) = tc[0]; *(d++) = tc[1];
      return 1;
  }
  else {
      float ab[3], ac[3], bc[3];
      for (int i = 0; i < 3; i++) {
          ab[i] = (a[i] + b[i]) / 2;
          ac[i] = (a[i] + c[i]) / 2;
          bc[i] = (b[i] + c[i]) / 2;
      }
      normalize(ab + 0, ab + 1, ab + 2);
      normalize(ac + 0, ac + 1, ac + 2);
      normalize(bc + 0, bc + 1, bc + 2);
      float tab[2], tac[2], tbc[2];
      tab[0] = 0; tab[1] = 1 - acosf(ab[1]) / PI;
      tac[0] = 0; tac[1] = 1 - acosf(ac[1]) / PI;
      tbc[0] = 0; tbc[1] = 1 - acosf(bc[1]) / PI;
      int total = 0;
      int n;
      n = _MakeSphere(data, r, detail - 1, a, ab, ac, ta, tab, tac);
      total += n; data += n * 24;
      n = _MakeSphere(data, r, detail - 1, b, bc, ab, tb, tbc, tab);
      total += n; data += n * 24;
      n = _MakeSphere(data, r, detail - 1, c, ac, bc, tc, tac, tbc);
      total += n; data += n * 24;
      n = _MakeSphere(data, r, detail - 1, ab, bc, ac, tab, tbc, tac);
      total += n; data += n * 24;
      return total;
  }
}

void SkyRenderer::GenerateBuffer() {
    GLfloat* data = new GLfloat[SKY_DATA_SIZE];
    size = sizeof(data)*SKY_DATA_SIZE/2;
    MakeSphere(data,1, 3);
    glGenBuffers(1, &SkyBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, SkyBuffer);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    delete [] data;
}
