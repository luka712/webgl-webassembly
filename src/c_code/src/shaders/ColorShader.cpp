#include "../../headers/shader.h"

ColorShader::ColorShader()
{
    auto source = BaseShader::GetSourceFromPath(COLOR_SHADER_PATH);
    Load(source.vertexSource.c_str(), source.fragmentSource.c_str());
    auto vb = new SquareVertexBuffer("a_position");
    AddVertexBuffer(vb);
    auto ib = new SquareIndexBuffer();
    AddIndexBuffer(ib);
    SetColor(Vec4(0, 0, 1, 1));
    glm::mat4 projection = glm::ortho(0.f, 1.f, 0.75f, 0.f, 0.0f, 1000.f);
    SetProjection(projection);
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

void ColorShader::SetProjection(glm::mat4 const &projection)
{
    SetMatrix4("u_projection", projection);
}

