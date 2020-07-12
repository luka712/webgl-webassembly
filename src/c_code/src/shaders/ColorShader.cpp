#include "../../headers/shader.h"
#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>

ColorShader::ColorShader()
{
    // get and load shaders
    auto source = BaseShader::GetSourceFromPath(COLOR_SHADER_PATH);
    Compile(source.vertexSource.c_str(), source.fragmentSource.c_str());

    // create buffers
    // auto vb = new QuadVertexBuffer("a_position");
    // AddVertexBuffer(vb);
    // auto ib = new QuadIndexBuffer();
    // AddIndexBuffer(ib);

    // set uniforms
    SetColor(glm::vec4(0, 0, 1, 1));

    // Remove later
    SetMatrix4("u_transform", glm::mat4(1.0f));

    StopProgram();
}

ColorShader::~ColorShader()
{
    DestroyShader();
}

void ColorShader::SetColor(glm::vec4 const &vec)
{
    SetUniform4fv("u_color", glm::vec4(vec.x, vec.y, vec.z, vec.w));
}
