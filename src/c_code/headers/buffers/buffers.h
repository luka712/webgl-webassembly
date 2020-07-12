#pragma once

#include <GLES3/gl3.h>
#include <stdio.h>

/**
 * @brief  The vertex buffer
 * @note   Lowest possibe buffer entry which goes directly over to GPU. It is used to build a mesh.
 */
class VertexBuffer
{
private:
    const GLchar *name;
    GLuint attributeLoc;
    GLuint buffer;
    const float *data;
    GLint size;
    int length;
    bool isBound = false;

public:
    /**
     * @brief  Vertex buffer constructor.
     * @note   Constructor for vertex buffer.
     * @param  *name: name which should correspond to name of attribute in shader, for exampe a_position for shader attribute vec3 a_positon.
     * @param  size: size of attribute in shader. Should be limited to size between 1 and 4. For example for attribute vec3 pass 3.
     * @param  *data: vertices data.
     * @param  length: length of data.
     */
    VertexBuffer(const GLchar *name, const GLint size, const float *data, const int length);
    ~VertexBuffer();
    GLuint GetBuffer() const { return this->buffer; };
    bool IsBound() const { return isBound; }
    void Initialize(const GLuint program);
    void Bind();
    void Unbind();
    void DeleteBuffer();
};

/**
 * @brief  The index buffer.
 * @note   Lowest possibe index buffer entry which goes directly over to GPU. It is used to build a mesh.
 */
class IndexBuffer
{
private:
    const GLuint *data;
    int length;
    GLuint buffer;
    bool isBound = false;

public:
    /**
     * @brief  Index buffer constructor.
     * @note   Constructor for index buffer.
     * @param  *data: index buffer data of unsigned integers.
     * @param  length: length of data.
     * @retval 
     */
    IndexBuffer(const GLuint *data, const int length);
    ~IndexBuffer();
    GLuint GetBuffer() const { return this->buffer; };
    bool IsBound() const { return isBound; }
    const int GetLength() const { return length; }
    void Initialize(const GLuint program);
    void Bind();
    void Unbind();
    void DeleteBuffer();
};

class QuadVertexBuffer : public VertexBuffer
{
private:
    const float data[12] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5, 0.0,
        0.5, -0.5, 0.0,
        0.5, 0.5, 0.0};

public:
    QuadVertexBuffer(const GLchar *name = "a_position") : VertexBuffer(name, 3, data, 12){};
};

class QuadIndexBuffer : public IndexBuffer
{
private:
    const GLuint data[6] = {
        0, 1, 2,
        1, 3, 2};

public:
    QuadIndexBuffer() : IndexBuffer(data, 6) {}
};