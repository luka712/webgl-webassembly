#include "../../headers/scene/scenemanager.h"
#include "../../headers/mesh/mesh.h"

CubeMesh::CubeMesh() : Mesh()
{
    LOG_CONSTRUCTOR();

    this->vbuffers = new std::list<std::shared_ptr<VertexBuffer>>;
    auto vbuffer = std::make_shared<CubeVertexBuffer>();
    vbuffers->push_back(vbuffer);
    ibuffer = std::make_shared<CubeIndexBuffer>();

    SetupMaterialAndMoveToScene();
}

EMSCRIPTEN_BINDINGS(CubeMesh)
{

    emscripten::class_<CubeMesh, emscripten::base<Mesh>>("CubeMesh")
        .smart_ptr_constructor("CubeMesh", &std::make_shared<CubeMesh>);
}