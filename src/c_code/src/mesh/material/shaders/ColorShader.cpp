#include "../../../../headers/mesh/material//shader/shader.h"
#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>

ColorShader::ColorShader() : BaseShader("color_shader")
{
    LOG_CONSTRUCTOR();
    // get and load shaders
    auto source = BaseShader::GetSourceFromPath(COLOR_SHADER_PATH);
    Compile(source.vertexSource.c_str(), source.fragmentSource.c_str());

    // set uniforms
    SetColor(glm::vec4(0, 0, 1, 1));

    // Remove later
    SetMatrix4("u_transform", glm::mat4(1.0f));

    StopProgram();
}

ColorShader::~ColorShader()
{
    LOG_DESTRUCTOR();
    DestroyShader();
}

void ColorShader::SetColor(glm::vec4 const &vec)
{
    SetUniform4fv("u_color", glm::vec4(vec.x, vec.y, vec.z, vec.w));
}
