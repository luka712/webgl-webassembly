#include <stdexcept>

#include "../../headers/scene/scenemanager.h"
#include "../../headers/mesh/mesh.h"

QuadMesh::QuadMesh() : Mesh()
{
    vbuffers.push_back(new QuadVertexBuffer());
    ibuffer = new QuadIndexBuffer();
    auto scene = SceneManager::GetInstance()->GetCurrentScene();
    printf("Scene: %p\n", &scene);
    auto materials = scene->GetMaterials();
    printf("Materials: %p\n", &materials);
    material = materials->front();
    printf("Material: %p\n", &material);
    if (!material->GetShader()->IsCompiled())
    {
        printf("Shader is not compiled. QuadMesh\n");
        //throw std::runtime_error(std::string("Shader is not compiled. QuadMesh"));
    }
    material->GetShader()->AddVertexBuffer(vbuffers.front());
    if (!vbuffers.front()->IsBound())
    {
        printf("Vertex buffer is not bound. QuadMesh\n");
        //throw std::runtime_error(std::string("Vertex buffer is not bound. QuadMesh"));
    }
    material->GetShader()->AddIndexBuffer(ibuffer);
    if (!ibuffer->IsBound())
    {
        printf("Index buffer is not bound. QuadMesh\n");
       // throw std::runtime_error(std::string("Index buffer is not bound. QuadMesh"));
    }

    SceneManager::GetInstance()->GetCurrentScene()->AddMesh(this);
}