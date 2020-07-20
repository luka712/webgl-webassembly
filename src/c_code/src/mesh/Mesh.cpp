#include <stdexcept>

#include "../../headers/scene/scenemanager.h"
#include "../../headers/mesh/mesh.h"

Mesh::Mesh()
{
    this->transform = std::make_shared<Transform>();
}

Mesh::Mesh(std::shared_ptr<VertexBuffer> vb, std::shared_ptr<IndexBuffer> ib) : Mesh()
{
    this->vbuffers = new std::list<std::shared_ptr<VertexBuffer>>;
    this->vbuffers->push_back(vb);
    this->ibuffer = ib;

    SceneManager::GetInstance()->GetCurrentScene()->AddMesh(shared_from_this());
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
}

void Mesh::SetupMaterialAndMoveToScene()
{
    LOG("SetupMaterialAndMoveToScene called.");
    material = SceneManager::GetInstance()->GetCurrentScene()->GetMaterials()->front();

    if (!material->GetShader()->IsCompiled())
    {
        LOG("Shader is not compiled\n");
        throw std::runtime_error(std::string("Shader is not compiled. QuadMesh"));
    }
    material->GetShader()->AddVertexBuffer(vbuffers->front());
    if (!vbuffers->front()->IsBound())
    {
        LOG("Vertex buffer is not bound.\n");
        throw std::runtime_error(std::string("Vertex buffer is not bound. QuadMesh"));
    }
    material->GetShader()->AddIndexBuffer(ibuffer);
    if (!ibuffer->IsBound())
    {
        LOG("Vertex buffer is not bound.\n");
        throw std::runtime_error(std::string("Index buffer is not bound. QuadMesh"));
    }

    LOG("Trying to add mesh.");// TODO: Fails here 
    // SceneManager::GetInstance()->GetCurrentScene()->AddMesh(shared_from_this());
    LOG("SetupMaterialAndMoveToScene finished.");
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
        .smart_ptr_constructor("Mesh", &std::make_shared<Mesh>)
        .function("Translate", &Mesh::Translate)
        .function("Scale", &Mesh::Scale)
        .function("Rotation", &Mesh::Rotation)
        .function("GetTransform", &Mesh::GetTransform, emscripten::allow_raw_pointers());
}