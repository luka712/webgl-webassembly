#include "../../headers/buffers/buffers.h"

VertexBuffer::VertexBuffer(const GLchar *name, const GLint size, const float *data, const int length)
{
    this->name = name;
    this->data = data;
    this->size = size;
    this->length = length;
}

VertexBuffer::~VertexBuffer()
{
    Unbind();
    DeleteBuffer();
}

void VertexBuffer::Initialize(const GLuint program)
{
    attributeLoc = glGetAttribLocation(program, name);
    DEBUG_PRINT_FORMAT("Attribute location: %d", attributeLoc);

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * length, data, GL_STATIC_DRAW);

    DEBUG_PRINT_FORMAT("Vertex buffer id: %d", buffer);

    if (buffer <= 0)
    {
        printf("Vertex buffer not bound %d\n", buffer);
    }

    glEnableVertexAttribArray(attributeLoc);
    glVertexAttribPointer(attributeLoc, size, GL_FLOAT, GL_FALSE, 0, 0);

    isBound = true;
}

void VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glEnableVertexAttribArray(attributeLoc);
    glVertexAttribPointer(attributeLoc, size, GL_FLOAT, GL_FALSE, 0, 0);
}

void VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::DeleteBuffer()
{
    glDeleteBuffers(1, &buffer);
}