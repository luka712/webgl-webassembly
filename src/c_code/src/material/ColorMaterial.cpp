#include "../../headers/material/material.h"


ColorMaterial::ColorMaterial()
{
    LOG_CONSTRUCTOR();
    shader = std::make_shared<ColorShader>();
}