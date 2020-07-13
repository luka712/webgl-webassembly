#include <stdexcept>

#include "../../headers/scene/scenemanager.h"
#include "../../headers/mesh/mesh.h"

Mesh::Mesh()
{
    this->transform = new Transform();
}

Mesh::Mesh(VertexBuffer *vb, IndexBuffer *ib) : Mesh()
{
    this->vbuffers = new std::list<VertexBuffer *>;
    this->vbuffers->push_back(vb);
    this->ibuffer = ib;

    SceneManager::GetInstance()->GetCurrentScene()->AddMesh(this);
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

    auto meshes = SceneManager::GetInstance()->GetCurrentScene()->GetMeshes();
    meshes->remove(this);
}

void Mesh::SetupMaterialAndMoveToScene()
{
    material = SceneManager::GetInstance()->GetCurrentScene()->GetMaterials()->front();

    if (!material->GetShader()->IsCompiled())
    {
        DEBUG_PRINT("Shader is not compiled\n");
        throw std::runtime_error(std::string("Shader is not compiled. QuadMesh"));
    }
    material->GetShader()->AddVertexBuffer(vbuffers->front());
    if (!vbuffers->front()->IsBound())
    {
        DEBUG_PRINT("Vertex buffer is not bound.\n");
        throw std::runtime_error(std::string("Vertex buffer is not bound. QuadMesh"));
    }
    material->GetShader()->AddIndexBuffer(ibuffer);
    if (!ibuffer->IsBound())
    {
        DEBUG_PRINT("Vertex buffer is not bound.\n");
        throw std::runtime_error(std::string("Index buffer is not bound. QuadMesh"));
    }

    SceneManager::GetInstance()->GetCurrentScene()->AddMesh(this);
}

void Mesh::BindBuffers()
{
    for (auto const &vb : *vbuffers)
    {
        vb->Bind();
    }
    ibuffer->Bind();
}

void Mesh::UnbindBuffers()
{
    for (auto const &vb : *vbuffers)
    {
        vb->Unbind();
    }
    ibuffer->Unbind();
}

void Mesh::UseShader()
{
    material->GetShader()->UseProgram();
}

void Mesh::StopShader()
{
    material->GetShader()->StopProgram();
}

// void Mesh::Translate(glm::vec3 v)
// {
//     this->transform->position->x = v.x;
//     this->transform->position->y = v.y;
//     this->transform->position->z = v.z;
// }

void Mesh::Translate(float x, float y, float z)
{
    this->transform->position->x = x;
    this->transform->position->y = y;
    this->transform->position->z = z;
}

void Mesh::Scale(float x, float y, float z)
{
    this->transform->scale->x = x;
    this->transform->scale->y = y;
    this->transform->scale->z = z;
}

void Mesh::Rotation(float x, float y, float z)
{
    this->transform->rotation->x = x;
    this->transform->rotation->y = y;
    this->transform->rotation->z = z;
}

EMSCRIPTEN_BINDINGS(Mesh)
{

    emscripten::class_<Mesh>("Mesh")
        .constructor()
        .function("Translate", &Mesh::Translate)
        .function("Scale", &Mesh::Scale)
        .function("Rotation", &Mesh::Rotation)
        .function("GetTransform", &Mesh::GetTransform, emscripten::allow_raw_pointers());
}