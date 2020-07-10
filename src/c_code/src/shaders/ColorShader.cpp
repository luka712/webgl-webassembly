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
}

ColorShader::~ColorShader()
{
    DestroyShader();
}

void  ColorShader::SetColor(Vec4 const &vec)
{
    setUniform4fv("u_color",Vec4(vec.x, vec.y, vec.z, vec.w));
}