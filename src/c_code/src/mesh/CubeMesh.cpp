#include "../../headers/scene/scenemanager.h"
#include "../../headers/mesh/mesh.h"

CubeMesh::CubeMesh() : Mesh()
{
    this->vbuffers = new std::list<VertexBuffer *>;
    vbuffers->push_back(new CubeVertexBuffer());
    ibuffer = new CubeIndexBuffer();

    SetupMaterialAndMoveToScene();
}

EMSCRIPTEN_BINDINGS(CubeMesh)
{

    emscripten::class_<CubeMesh, emscripten::base<Mesh>>("CubeMesh")
        .constructor();
}