#include "../../headers/mesh/mesh.h"

QuadMesh::QuadMesh(std::string id) : Mesh(id)
{
    LOG_CONSTRUCTOR();
    geometry = std::make_shared<QuadGeometry>();
    material = std::make_shared<ColorMaterial>();
}

QuadMesh::QuadMesh() : Mesh("quad_mesh")
{
    LOG_CONSTRUCTOR();
    geometry = std::make_shared<QuadGeometry>();
    material = std::make_shared<ColorMaterial>();
}

// EMSCRIPTEN_BINDINGS(QuadMesh)
// {

//     emscripten::class_<QuadMesh, emscripten::base<Mesh>>("QuadMesh")
//         .smart_ptr_constructor("QuadMesh", &std::make_shared<QuadMesh>);
// }