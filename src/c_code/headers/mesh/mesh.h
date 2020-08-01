#pragma once

#include <list>
#include <emscripten.h>
#include <emscripten/bind.h>
#include "./material/material.h"
#include "./geometry/geometry.h"
#include "../component/component.h"

//TODO: Move buffer data to geometry class it should be like this -> Renderable object -> Mesh -> (Geometry, Material)

/*
 * Mesh -> VertexBuffer[], IndexBuffer
 */

/**
 * @brief  The mesh
 * @note   Mesh is abstraction which contains VertexBuffers and IndexBuffer.
 */
class Mesh : public Component, std::enable_shared_from_this<Mesh>
{
public:
    std::shared_ptr<Material> material;
    std::shared_ptr<Geometry> geometry;
    bool isCompiled;


    Mesh(std::string id, std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material);
    Mesh(std::string id);
    ~Mesh();

    void Initialize() override;

    //TODO: MOVE TRANSOFRM TO RENDERABLE
    void SetMaterial(std::shared_ptr<Material> mat) { material = mat; }
};

class QuadMesh : public Mesh
{
public:
    QuadMesh(std::string id);
    QuadMesh();
};

class CubeMesh : public Mesh
{
public:
    CubeMesh(std::string id);
    CubeMesh();
};
