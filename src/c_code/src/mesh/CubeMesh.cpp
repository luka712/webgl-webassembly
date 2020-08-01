#include "../../headers/mesh/mesh.h"

CubeMesh::CubeMesh(std::string id) : Mesh(id)
{
    LOG_CONSTRUCTOR();
    geometry = std::make_shared<CubeGeometry>();
    material = std::make_shared<ColorMaterial>();
}

CubeMesh::CubeMesh() : Mesh("cube_mesh")
{
    LOG_CONSTRUCTOR();
    geometry = std::make_shared<CubeGeometry>();
    material = std::make_shared<ColorMaterial>();
}

// EMSCRIPTEN_BINDINGS(CubeMesh)
// {

//     emscripten::class_<CubeMesh, emscripten::base<Mesh>>("CubeMesh")
//         .smart_ptr_constructor("CubeMesh", &std::make_shared<CubeMesh>);
// }