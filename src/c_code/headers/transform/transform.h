#pragma once

#include <emscripten.h>
#include <emscripten/bind.h>
#include "../../../../include/glm/glm.hpp"
#include "../../../../include/glm/ext.hpp"

class Transform
{
public:
    glm::mat4 transform;
    glm::vec3 *position;
    glm::vec3 *scale;
    glm::vec3 *rotation;
    Transform()
    {
        transform = glm::mat4(1.0f);
        position = new glm::vec3(0.0f);
        scale = new glm::vec3(1.0f);
        rotation = new glm::vec3(0.0f);
    }
    glm::vec3 *GetPosition() { return position; }
    void SetPosition(glm::vec3 *v) { position = v; }

    glm::vec3 *GetScale() { return scale; }
    void SetScale(glm::vec3 *v) { scale = v; }

    glm::vec3 *GetRotation() { return rotation; }
    void SetRotation(glm::vec3 *v) { rotation = v; }

    void ApplyTransformations();
};
