#include "../headers/renderer.h"

Renderer::Renderer()
    : Renderer(800, 600)
{
}

Renderer::Renderer(int width, int height)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, 0, &this->window, &this->renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

Renderer::~Renderer()
{
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

    for (auto const &shd : shaders)
    {
        shd->UseProgram();

        // for no there would be no cases of drawing without indices
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, shd->GetLength(), GL_UNSIGNED_INT, 0);
        
        shd->StopProgram();
    }
}

void Renderer::ClearColor(float r, float g, float b, float a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}