#include "../../headers/buffers/buffers.h"

VertexBuffer::VertexBuffer(const GLchar *name, const GLint size, const float *data, const int length)
{
    LOG_CONSTRUCTOR();
    this->name = name;
    this->data = data;
    this->size = size;
    this->length = length;
}

VertexBuffer::VertexBuffer(const GLint location, const GLint size, const float *data, const int length)
{
    LOG_CONSTRUCTOR();
    this->attributeLoc = location;
    this->data = data;
    this->size = size;
    this->length = length;
}


VertexBuffer::~VertexBuffer()
{
    LOG_DESTRUCTOR();
    Unbind();
    DeleteBuffer();
}

void VertexBuffer::Initialize(const GLuint program)
{
    // meaning it was not bound. attribute location can be passed in case where shader has layout(location = {location}) on attribute
    if(attributeLoc < 0)
    {
        attributeLoc = glGetAttribLocation(program, name);
    }
    LOG_FORMAT("Attribute location: %d", attributeLoc);

    glGenBuffers(1, &buffer);
    LOG_FORMAT("Generated vertex buffer: %u", buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * length, data, GL_STATIC_DRAW);

    LOG_FORMAT("Vertex buffer id: %d", buffer);

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
    LOG_FORMAT("Destroying vertex buffer: %u", buffer);
    glDeleteBuffers(1, &buffer);
    LOG_FORMAT("Destroyed vertex buffer: %u", buffer);
}