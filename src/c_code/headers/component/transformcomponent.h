
#pragma once

#include "../../../../include/glm/glm.hpp"

#include "../constants.h"
#include "component.h"

class TransformComponent : public Component
{
public:
    std::shared_ptr<glm::vec3> position;
    std::shared_ptr<glm::vec3> rotation;
    std::shared_ptr<glm::vec3> scale;
    glm::mat4 transform;

    TransformComponent();
    TransformComponent(glm::vec3 pos,glm::vec3 rot,glm::vec3 scl);

    void Update() override;
};

