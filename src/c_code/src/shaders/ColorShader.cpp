#include "../../headers/shader.h"
#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>

ColorShader::ColorShader(Camera *camera)
{
    this->camera = camera;

    // get and load shaders 
    auto source = BaseShader::GetSourceFromPath(COLOR_SHADER_PATH);
    Load(source.vertexSource.c_str(), source.fragmentSource.c_str());

    // create buffers
    auto vb = new SquareVertexBuffer("a_position");
    AddVertexBuffer(vb);
    auto ib = new SquareIndexBuffer();
    AddIndexBuffer(ib);

    // set uniforms
    SetColor(Vec4(0, 0, 1, 1));
    SetMatrix4(camera->getViewAttrName().c_str(), camera->getViewMatrix());
    SetMatrix4(camera->getProjectionAttrName().c_str(), camera->getProjectionMatrix());
    
    // Remove later
    SetMatrix4("u_transform", glm::mat4(1.0f));

    StopProgram();
}

ColorShader::~ColorShader()
{
    DestroyShader();
}

void ColorShader::SetColor(Vec4 const &vec)
{
    SetUniform4fv("u_color",Vec4(vec.x, vec.y, vec.z, vec.w));
}
