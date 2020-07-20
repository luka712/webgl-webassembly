#include <stdexcept>

#include "../../headers/scene/scenemanager.h"
#include "../../headers/mesh/mesh.h"

QuadMesh::QuadMesh() : Mesh()
{
    LOG_CONSTRUCTOR();

    this->vbuffers = new std::list<std::shared_ptr<VertexBuffer>>;
    auto vbuffer = std::make_shared<QuadVertexBuffer>();
    vbuffers->push_back(vbuffer);
    ibuffer = std::make_shared<QuadIndexBuffer>();

    SetupMaterialAndMoveToScene();
}

EMSCRIPTEN_BINDINGS(QuadMesh)
{

    emscripten::class_<QuadMesh, emscripten::base<Mesh>>("QuadMesh")
        .smart_ptr_constructor("QuadMesh", &std::make_shared<QuadMesh>);
}