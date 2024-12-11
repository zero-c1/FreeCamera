#pragma once

#include <glm/glm.hpp>

namespace MyApp
{

class Camera
{
public:
    Camera() = default;

    Camera(glm::vec3 eye, glm::vec3 lookat, glm::vec3 upVector);

    glm::mat4 getViewMatrix() const;
    glm::vec3 getEye() const;
    glm::vec3 getUpVector() const;
    glm::vec3 getLookAt() const;

    // equals to normalize(eye - lookAt)
    glm::vec3 getViewDir() const;
    glm::vec3 getRightVector() const;

    void setCameraView(glm::vec3 eye, glm::vec3 lookat, glm::vec3 up);
    void arcballRotate(const float deltaAngleX, const float deltaAngleY);
    void pan(const float deltaAngleX, const float deltaAngleY);
    void scale(const float delta);
    void updateViewMatrix();

private:
    glm::mat4 mViewMatrix;
    glm::vec3 mEye; // Camera position in 3D
    glm::vec3 mLookAt; // Point that the camera is looking at
    glm::vec3 mUpVector; // Orientation of the camera

    const float cosThreshold {1 - glm::cos(glm::radians(1.0f))};

};

} // namespace MyApp