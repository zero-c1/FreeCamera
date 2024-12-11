#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

MyApp::Camera::Camera(glm::vec3 eye, glm::vec3 lookat, glm::vec3 upVector)
    : mEye(std::move(eye))
    , mLookAt(std::move(lookat))
    , mUpVector(std::move(upVector))
{
    updateViewMatrix();
}

glm::mat4 MyApp::Camera::getViewMatrix() const
{
    return mViewMatrix;
}

glm::vec3 MyApp::Camera::getEye() const
{
    return mEye;
}

glm::vec3 MyApp::Camera::getUpVector() const
{
    return mUpVector;
}

glm::vec3 MyApp::Camera::getLookAt() const
{
    return mLookAt;
}

glm::vec3 MyApp::Camera::getViewDir() const
{
    return glm::transpose(mViewMatrix)[2];
}

glm::vec3 MyApp::Camera::getRightVector() const
{
    return glm::transpose(mViewMatrix)[0];
}

void MyApp::Camera::arcballRotate(const float deltaAngleX, const float deltaAngleY)
{
    glm::vec4 eye(mEye, 1);
    glm::vec4 lookAt(mLookAt, 1);

    auto rotationMatrix {glm::rotate(glm::identity<glm::mat4>(), glm::radians(-deltaAngleX), mUpVector)};
    auto newEye {rotationMatrix * (eye - lookAt) + lookAt};

    rotationMatrix = glm::rotate(glm::identity<glm::mat4>(), glm::radians(-deltaAngleY), getRightVector());
    newEye = rotationMatrix * (newEye - lookAt) + lookAt;
    auto newUpVector {rotationMatrix * glm::vec4(mUpVector, 1.0f)};

    setCameraView(newEye, mLookAt, newUpVector);
}

void MyApp::Camera::pan(const float deltaAngleX, const float deltaAngleY)
{
    auto cameraUpVector {glm::cross(getRightVector(), getViewDir())};
    auto newLookAt {mLookAt - deltaAngleX * getRightVector() - deltaAngleY * cameraUpVector};
    auto newEye {mEye - deltaAngleX * getRightVector() - deltaAngleY * cameraUpVector};
    setCameraView(newEye, newLookAt, mUpVector);
}

void MyApp::Camera::scale(const float delta)
{
    auto viewDir {mEye - mLookAt};
    auto newEye {viewDir * (1.0f + delta) + mLookAt};
    setCameraView(newEye, mLookAt, mUpVector);
}

void MyApp::Camera::setCameraView(glm::vec3 eye, glm::vec3 lookat, glm::vec3 up)
{
    mEye = std::move(eye);
    mLookAt = std::move(lookat);
    mUpVector = std::move(up);
    updateViewMatrix();
}

void MyApp::Camera::updateViewMatrix()
{
    // Generate view matrix using the eye, lookAt and up vector
    mViewMatrix = glm::lookAt(mEye, mLookAt, mUpVector);
}
