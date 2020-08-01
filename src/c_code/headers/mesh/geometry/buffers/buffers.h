#pragma once

#include <GLES3/gl3.h>
#include <stdio.h>
#include "../../../constants.h"

/**
 * @brief  The vertex buffer
 * @note   Lowest possibe buffer entry which goes directly over to GPU. It is used to build a mesh.
 */
class VertexBuffer : public IId
{
private:
    const GLchar *name;
    // default is -1. In this case property name is used, as layout location was never set via constructor.
    GLuint attributeLoc = -1;
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
    VertexBuffer(std::string id, const GLchar *name, const GLint size, const float *data, const int length);
    /**
     * @brief  Vertex buffer constructor.
     * @note   Constructor for vertex buffer
     * @param  location: used to bind directly to shader with layout (location = {location}) property
     * @param  size: size of attribute in shader. Should be limited to size between 1 and 4. For example for attribute vec3 pass 3.
     * @param  *data: vertices data.
     * @param  length: length of data.: 
     * @retval 
     */
    VertexBuffer(std::string id, const GLint location, const GLint size, const float *data, const int length);
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
class IndexBuffer : public IId
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
    IndexBuffer(std::string id, const GLuint *data, const int length);
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
    const GLfloat data[12] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5, 0.0,
        0.5, -0.5, 0.0,
        0.5, 0.5, 0.0};

public:
    QuadVertexBuffer() : VertexBuffer("quad_positon_data", 0, 3, data, 12){};
};

class QuadIndexBuffer : public IndexBuffer
{
private:
    const GLuint data[6] = {
        0, 1, 2,
        1, 3, 2};

public:
    QuadIndexBuffer() : IndexBuffer("quad_indices_data", data, 6) {}
};

class CubeVertexBuffer : public VertexBuffer
{
    const GLfloat data[24] = {
        // front
        -0.5, -0.5, 0.5,
        0.5, -0.5, 0.5,
        0.5, 0.5, 0.5,
        -0.5, 0.5, 0.5,
        // back
        -0.5, -0.5, -0.5,
        0.5, -0.5, -0.5,
        0.5, 0.5, -0.5,
        -0.5, 0.5, -0.5};

public:
    CubeVertexBuffer() : VertexBuffer("cube_position_data", 0, 3, data, 24){};
};

class CubeIndexBuffer : public IndexBuffer
{
    const GLuint data[36] = {
        // front
        0, 1, 2,
        2, 3, 0,
        // right
        1, 5, 6,
        6, 2, 1,
        // back
        7, 6, 5,
        5, 4, 7,
        // left
        4, 0, 3,
        3, 7, 4,
        // bottom
        4, 5, 1,
        1, 0, 4,
        // top
        3, 2, 6,
        6, 7, 3};

public:
    CubeIndexBuffer() : IndexBuffer("cube_indices_data", data, 36){};
};