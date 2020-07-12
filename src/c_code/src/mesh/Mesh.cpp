
#include "../../headers/scene/scenemanager.h"
#include "../../headers/mesh/mesh.h"

Mesh::Mesh()
{
    this->transform = new Transform();
}

Mesh::Mesh(VertexBuffer *vb, IndexBuffer *ib) : Mesh()
{
    this->vbuffers.push_back(vb);
    this->ibuffer = ib;

    SceneManager::GetInstance()->GetCurrentScene()->AddMesh(this);
}

Mesh::~Mesh()
{
    for (auto it = vbuffers.begin(); it != vbuffers.end(); ++it)
    {
        delete &it;
    }
    delete &vbuffers;
    delete ibuffer;
}

void Mesh::BindBuffers()
{
    for (auto const &vb : vbuffers)
    {
        vb->Bind();
    }
    ibuffer->Bind();
}

void Mesh::UnbindBuffers()
{
    for (auto const &vb : vbuffers)
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