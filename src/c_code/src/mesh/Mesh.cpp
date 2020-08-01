#include <stdexcept>

#include "../../headers/scene/scenemanager.h"
#include "../../headers/mesh/mesh.h"


Mesh::Mesh(std::string id, std::shared_ptr<Geometry> geo, std::shared_ptr<Material> mat) : Mesh(id)
{
    LOG_CONSTRUCTOR();
    geometry = geo;
    material = mat;
}

Mesh::Mesh(std::string id) 
{
    LOG_CONSTRUCTOR();
    this->id = id;
    type = ObjectType::MeshType;
}

Mesh::~Mesh()
{
    //TODO: review
    // for (auto it = vbuffers->begin(); it != vbuffers->end(); ++it)
    // {
    //     delete &it;
    // }
    // delete vbuffers;
    // delete ibuffer;
}

void Mesh::Initialize()
{
    material->GetShader()->UseProgram();
    geometry->InitializeBuffers(material->GetShader()->GetProgram());

    // geometry->UnbindBuffers();
    // material->GetShader()->StopProgram();
}

// void Mesh::Translate(glm::vec3 v)
// {
//     this->transform->position->x = v.x;
//     this->transform->position->y = v.y;
//     this->transform->position->z = v.z;
// }

// EMSCRIPTEN_BINDINGS(Mesh)
// {

//     emscripten::class_<Mesh>("Mesh")
//         .smart_ptr_constructor("Mesh", &std::make_shared<Mesh>)
//         .function("Translate", &Mesh::Translate)
//         .function("Scale", &Mesh::Scale)
//         .function("Rotation", &Mesh::Rotation)
//         .function("GetTransform", &Mesh::GetTransform, emscripten::allow_raw_pointers());
// }