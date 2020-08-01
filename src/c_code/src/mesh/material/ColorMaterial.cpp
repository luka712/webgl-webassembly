#include "../../../headers/mesh/material/material.h"


ColorMaterial::ColorMaterial()
    : Material("color_material")
{
    LOG_CONSTRUCTOR();
    shader = std::make_shared<ColorShader>();
}