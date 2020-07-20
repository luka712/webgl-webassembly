#pragma once

#include <list>
#include <emscripten.h>
#include <emscripten/bind.h>
#include "../buffers/buffers.h"
#include "../transform/transform.h"
#include "../material/material.h"

//TODO: Move buffer data to geometry class it should be like this -> Renderable object -> Mesh -> (Geometry, Material)

/*
 * Mesh -> VertexBuffer[], IndexBuffer
 */

/**
 * @brief  The mesh
 * @note   Mesh is abstraction which contains VertexBuffers and IndexBuffer.
 */
class Mesh : public std::enable_shared_from_this<Mesh>
{

private:
    unsigned long id = 1;

protected:
    std::shared_ptr<Material> material;
    std::list<std::shared_ptr<VertexBuffer>> *vbuffers;
    std::shared_ptr<IndexBuffer> ibuffer;
    std::shared_ptr<Transform> transform;
    bool isCompiled;

    void SetupMaterialAndMoveToScene();

public:
    Mesh();
    Mesh(std::shared_ptr<VertexBuffer> vbuffer, std::shared_ptr<IndexBuffer> ibuffer);
    ~Mesh();
    std::shared_ptr<IndexBuffer> GetIndexBuffer() const { return ibuffer; }
    void BindBuffers();
    void UnbindBuffers();
    void UseShader();
    void StopShader();

    //TODO: MOVE TRANSOFRM TO RENDERABLE
    std::shared_ptr<Transform> GetTransform() { return transform; }
    void Translate(float x, float y, float z);
    void Scale(float x, float y, float z);
    void Rotation(float x, float y, float z);
    std::shared_ptr<Material> GetMaterial() { return material; }
    void SetMaterial(std::shared_ptr<Material> mat) { material = mat; }
};

class QuadMesh : public Mesh
{
public:
    QuadMesh();
};

class CubeMesh : public Mesh
{
public:
    CubeMesh();
};
