#pragma once

#include "../constants.h"
#include "../../../../include/glm/mat4x4.hpp"
#include "../../../../include/glm/matrix.hpp"
#include "../../../../include/glm/ext.hpp"

enum LightType
{
    None = 0,
    Ambient
};

class Light  
{
    protected:
        LightType type = LightType::None;

        LightType GetType() const { return type; }
};

class AmbientLight : public Light
{
    private:
        float strength = 0.1f;
        glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

    protected:
        LightType type = LightType::Ambient;

        float GetStrength() const { return strength; }
        glm::vec3 &GetColor() { return color; }
};