#include "../../headers/renderer/renderer.h"

Renderer::~Renderer()
{
}

bool Renderer::initialized = false;
Renderer *Renderer::instance;

Renderer *Renderer::GetInstance()
{
    if (Renderer::initialized == false)
    {
        Renderer::initialized = true;
        instance = new Renderer();
    }
    return instance;
}

void Renderer::Initialize(int width, int height)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Renderer::AddShader(BaseShader *shader)
{
    shaders.push_back(shader);
}

void Renderer::Draw()
{
    glClearColor(this->r, this->g, this->b, this->a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // for each thing to draw
    // 1. bind buffers and set attributes
    // 2. use program
    // 3. set uniforms and bind texture units
    // 4. call draw

    auto meshes = SceneManager::GetInstance()->GetCurrentScene()->GetMeshes();
    auto camera = SceneManager::GetInstance()->GetCurrentScene()->GetCamera();
    for (auto const &mesh : *meshes)
    {
        //TODO: optimization flags
        // meshes will have shaders which should be bound accordingly, possibly sorted properly due to optimization reasons.
        mesh->BindBuffers();

        mesh->UseShader();

        auto transform = mesh->GetTransform();
        transform->ApplyTransformations();
        mesh->GetMaterial()->GetShader()->SetMatrix4("u_transform", transform->transform);
        mesh->GetMaterial()->GetShader()->SetMatrix4("u_view", camera->getViewMatrix());
        mesh->GetMaterial()->GetShader()->SetMatrix4("u_projection", camera->getProjectionMatrix());

        glDrawElements(GL_TRIANGLES, mesh->GetIndexBuffer()->GetLength(), GL_UNSIGNED_INT, 0);

        mesh->StopShader();
    }
}

void Renderer::ClearColor(float r, float g, float b, float a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}