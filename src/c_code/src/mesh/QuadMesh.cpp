#include <stdexcept>

#include "../../headers/scene/scenemanager.h"
#include "../../headers/mesh/mesh.h"

QuadMesh::QuadMesh() : Mesh()
{
    this->vbuffers = new std::list<VertexBuffer *>;
    vbuffers->push_back(new QuadVertexBuffer());
    ibuffer = new QuadIndexBuffer();

    SetupMaterialAndMoveToScene();
}

EMSCRIPTEN_BINDINGS(QuadMesh)
{

    emscripten::class_<QuadMesh, emscripten::base<Mesh>>("QuadMesh")
        .constructor();
}