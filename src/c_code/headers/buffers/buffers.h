#include <GLES3/gl3.h>
#include <stdio.h>

class VertexBuffer
{
private:
    const GLchar *name;
    GLuint attributeLoc;
    GLuint buffer;
    const float *data;
    GLint size;
    int length;

public:
    VertexBuffer(const GLchar *name, const GLint size, const float *data, const int length);
    ~VertexBuffer();
    GLuint GetBuffer() const { return this->buffer; };
    void Initialize(const GLuint program);
    void Bind();
    void Unbind();
    void DeleteBuffer();
};

class IndexBuffer
{
private:
    const GLuint *data;
    int length;
    GLuint buffer;

public:
    IndexBuffer(const GLuint *data, const int length);
    ~IndexBuffer();
    GLuint GetBuffer() const { return this->buffer; };
    const int GetLength() const { return length; }
    void Initialize(const GLuint program);
    void Bind();
    void Unbind();
    void DeleteBuffer();
};

class SquareVertexBuffer : public VertexBuffer
{
private:
    const float data[12] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5, 0.0,
        0.5, -0.5, 0.0,
        0.5, 0.5, 0.0};

public:
    SquareVertexBuffer(const GLchar *name) : VertexBuffer(name, 3, data, 12){};
};

class SquareIndexBuffer : public IndexBuffer
{
private:
    const GLuint data[6] = {
        0, 1, 2,
        1, 3, 2};

public:
    SquareIndexBuffer() : IndexBuffer(data, 6) {}
};