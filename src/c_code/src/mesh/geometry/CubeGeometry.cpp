#include "../../../headers/mesh/geometry/geometry.h"

CubeGeometry::CubeGeometry() : Geometry("default_cube_geometry")
{
    LOG_CONSTRUCTOR();
    auto vbuffer = std::make_shared<CubeVertexBuffer>();
    vbuffers.emplace(vbuffer->id,vbuffer);
    ibuffer = std::make_shared<CubeIndexBuffer>();
}