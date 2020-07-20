#pragma once

#include <string>
#include "../constants.h"
#include "../../../../include/glm/mat4x4.hpp"
#include "../../../../include/glm/matrix.hpp"
#include "../../../../include/glm/ext.hpp"

class Camera
{
private:
    std::string projectAttrName = "u_projection";
    std::string viewAttrName = "u_view";

protected:
    glm::mat4 projection;
    glm::mat4 view;

public:
    std::string getProjectionAttrName() const { return projectAttrName; }
    void setProjectonAttrName(const std::string v) { projectAttrName = v; }
    std::string getViewAttrName() const { return viewAttrName; }
    void setViewAttrName(const std::string v) { viewAttrName = v; }

    glm::mat4 getProjectionMatrix() const { return projection; }
    glm::mat4 getViewMatrix() const { return view; }

    virtual void Move(glm::vec3 pos) {}
};

class PerspectiveCamera : public Camera
{
private:
    int screenWidth;
    int screenHeight;
    float fov;
    float near;
    float far;
    glm::vec3 pos;
    glm::vec3 lookAt;
    glm::vec3 up;

public:
    PerspectiveCamera(int screenWidth = DEFAULT_WIDTH,
                      int screenHeight = DEFAULT_HEIGHT,
                      float fov = DEFAULT_FOV,
                      float near = 0.0f,
                      float far = 100.0f,
                      glm::vec3 pos = glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3 lookAt = glm::vec3(0.0f, 0.0f, -1.0f),
                      glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
    ~PerspectiveCamera();

    void Move(glm::vec3 pos) override;
};