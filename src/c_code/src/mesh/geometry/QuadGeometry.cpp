#include "../../../headers/mesh/geometry/geometry.h"

QuadGeometry::QuadGeometry() : Geometry("default_quad_geometry")
{
    LOG_CONSTRUCTOR();
    auto vbuffer = std::make_shared<QuadVertexBuffer>();
    vbuffers.emplace(vbuffer->id, vbuffer);
    ibuffer = std::make_shared<QuadIndexBuffer>();
}