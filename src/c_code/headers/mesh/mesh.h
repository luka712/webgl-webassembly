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
class Mesh
{

private:
    unsigned long id = 1;

protected:
    Material *material;
    std::list<VertexBuffer *> *vbuffers;
    IndexBuffer *ibuffer;
    Transform *transform;
    bool isCompiled;

    void SetupMaterialAndMoveToScene();

public:
    Mesh();
    Mesh(VertexBuffer *vbuffer, IndexBuffer *ibuffer);
    ~Mesh();
    IndexBuffer *GetIndexBuffer() const { return ibuffer; }
    void BindBuffers();
    void UnbindBuffers();
    void UseShader();
    void StopShader();


    //TODO: MOVE TRANSOFRM TO RENDERABLE
    Transform *GetTransform() { return transform; }
    void Translate(float x, float y, float z);
    void Scale(float x, float y, float z);
    void Rotation(float x, float y, float z);
    Material *GetMaterial() { return material; }
    void SetMaterial(Material *mat) { material = mat; }
};

class QuadMesh : public Mesh
{
public:
    QuadMesh();
};

class CubeMesh: public Mesh {
    public:
        CubeMesh();
};
