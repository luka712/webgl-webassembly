#include "../../../headers/mesh/geometry/geometry.h"

Geometry::~Geometry()
{
    LOG_DESTRUCTOR();
}

void Geometry::InitializeBuffers(const GLuint program)
{
    glUseProgram(program);
    glGenVertexArrays(1, &vao);
    LOG_FORMAT("Bound vao: %u", vao);

    InitVertexBuffers(program);
    InitIndexBuffer(program);

    this->isCompiled = true;
    glBindVertexArray(0);
    glUseProgram(0);
}

void Geometry::InitVertexBuffers(const GLuint program)
{
    LOG_FORMAT("Binding vao: %u", vao);
    glBindVertexArray(vao);
    for (auto it = vbuffers.begin(); it != vbuffers.end(); it++)
    {
        auto vbuffer = it->second;
        vbuffer->Initialize(program);
        LOG_FORMAT("VBO vertex %u initialized", vbuffer->GetBuffer());
    }

    glBindVertexArray(0);
}

void Geometry::InitIndexBuffer(const GLuint program)
{
    LOG_FORMAT("Binding vao: %u", vao);
    glBindVertexArray(vao);
    ibuffer->Initialize(program);
    glBindVertexArray(0);
    LOG_FORMAT("VBO index %u initialized", ibuffer->GetBuffer());
}

void Geometry::BindBuffers()
{
    glBindVertexArray(vao);
    for (auto it = vbuffers.begin(); it != vbuffers.end(); it++)
    {
        auto vb = it->second;
        vb->Bind();
    }
    ibuffer->Bind();
}

void Geometry::UnbindBuffers()
{
    for (auto it = vbuffers.begin(); it != vbuffers.end(); it++)
    {
        auto vb = it->second;
        vb->Unbind();
    }
    ibuffer->Unbind();
    // glBindVertexArray(0);
}
