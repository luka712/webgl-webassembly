#include "../../headers/buffers/buffers.h"

IndexBuffer::IndexBuffer(const GLuint *data, const int length)
{
    LOG_CONSTRUCTOR();
    this->data = data;
    this->length = length;
}

IndexBuffer::~IndexBuffer()
{
    LOG_DESTRUCTOR();
    Unbind();
    DeleteBuffer();
}

void IndexBuffer::Initialize(const GLuint program)
{
    glGenBuffers(1, &buffer);
    LOG_FORMAT("Generated index buffer: %u", buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, length * sizeof(unsigned int), data, GL_STATIC_DRAW);

    if (buffer <= 0)
    {
        printf("Element buffer not bound %d\n", buffer);
    }

    isBound = true;
}

void IndexBuffer::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
}

void IndexBuffer::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::DeleteBuffer()
{
    LOG_FORMAT("Destroying index buffer: %d", buffer);
    glDeleteBuffers(1, &buffer);
    LOG_FORMAT("Destroyed index buffer: %d", buffer);
}