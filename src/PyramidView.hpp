#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "Shader.hpp"
#include "Camera.h"

namespace MyApp
{

const float CUBE_VERTICES[]
{
     0.5f,  0.5f, 0.5f,  // top right
     0.5f, -0.5f, 0.5f,  // bottom right
    -0.5f, -0.5f, 0.5f,  // bottom left
    -0.5f,  0.5f, 0.5f,  // top left 

     0.5f,  0.5f,-0.5f,  // top right
     0.5f, -0.5f,-0.5f,  // bottom right
    -0.5f, -0.5f,-0.5f,  // bottom left
    -0.5f,  0.5f,-0.5f   // top left 
};

const float TRN_VERTICES[]
{
    0.0f, 0.0f, 0.0f,    // origin
    1.0f, 0.0f, 0.0f,    // x
    0.0f, 1.0f, 0.0f,    // y
    0.0f, 0.0f, 1.0f,    // z
};

const unsigned int CUBE_INDICES[]
{
    0, 1, 3,
    1, 2, 3,
    
    0, 4, 5,
    1, 0, 5,

    3, 2, 7,
    2, 6, 7,

    2, 1, 5,
    6, 2, 5,

    3, 0, 4,
    3, 4, 7,

    4, 6, 5,
    7, 6, 4,
};

const unsigned int TRN_INDICES[]
{
    0, 2, 1,
    3, 2, 0,
    0, 3, 1,
    1, 2, 3,
};

class PyramidView
{
public:
    void init();
    void render();
    void renderGUI();
    void update();

protected:
    GLuint mVAO;
    GLuint mVBO;
    GLuint mEBO;

    Shader mShader;
    Camera mCamera;

    glm::vec3 mUpVector {0.0f, 1.0f, 0.0f};
    glm::vec3 mFinalPosition;

    glm::mat4 mModel;
    glm::mat4 mView;
    glm::mat4 mProjection;

    bool mDragged {false};
};

} // namespace MyApp
