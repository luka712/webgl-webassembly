#include "../../headers/renderer/renderer.h"

Renderer::~Renderer()
{
    LOG_DESTRUCTOR();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Renderer::initialized = false;
std::shared_ptr<Renderer>  Renderer::instance;

std::shared_ptr<Renderer>  Renderer::GetInstance()
{
    if (Renderer::initialized == false)
    {
        Renderer::initialized = true;
        instance = std::make_shared<Renderer>();
    }
    return instance;
}

void Renderer::Initialize(int width, int height)
{

    SDL_Init(SDL_INIT_VIDEO);

    // version needs to be setup before renderer creationg
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    // note the SDL_WINDOW_OPENGL flag
    LOG("Calling SDL_CreateWindowAndRenderer.");
    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_OPENGL, &window, &renderer);

    SDL_GL_CreateContext(window);

    LOG_FORMAT("GL Version: %s\n", glGetString(GL_VERSION));
    LOG_FORMAT("Vendor: %s renderer = %s\n", glGetString(GL_VENDOR), glGetString(GL_RENDERER));

    glEnable(GL_DEPTH_TEST);
}

void Renderer::AddShader(std::shared_ptr<BaseShader> shader)
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