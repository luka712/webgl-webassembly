#pragma once

#include "buffers/buffers.h"

/**
 * @brief  Geometry, usually made of vertex data buffers
 */
class Geometry : public IId
{
private:
    bool isCompiled;

protected:
    GLuint vao;
    std::shared_ptr<IndexBuffer> ibuffer;
    std::map<std::string, std::shared_ptr<VertexBuffer>> vbuffers;

    void InitVertexBuffers(const GLuint program);
    void InitIndexBuffer(const GLuint program);

public:
    Geometry(std::string id)
    {
        this->id = id;
        vbuffers = std::map<std::string, std::shared_ptr<VertexBuffer>>();
    }

    Geometry(std::string id, std::shared_ptr<VertexBuffer> vb, std::shared_ptr<IndexBuffer> ib)
        : Geometry(id)
    {
        ibuffer = ib;
        vbuffers.emplace(vb->id, vb);
    }

    ~Geometry();

    bool IsCompiled() const { return isCompiled; }
    std::shared_ptr<IndexBuffer> GetIndexBuffer() const { return ibuffer; }
    std::map<std::string, std::shared_ptr<VertexBuffer>> &GetVertexBuffers() { return vbuffers; }
    void InitializeBuffers(const GLuint program);
    void BindBuffers();
    void UnbindBuffers();
};

class QuadGeometry : public Geometry
{
public:
    QuadGeometry();
};

class CubeGeometry : public Geometry
{
public:
    CubeGeometry();
};
