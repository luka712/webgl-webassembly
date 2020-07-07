#include "../headers/renderer.h"

Renderer::Renderer()
    :Renderer(800, 600)
{
}

Renderer::Renderer(int width, int height)
{
    SDL_Init( SDL_INIT_VIDEO );
    SDL_CreateWindowAndRenderer( width, height, 0, &this->window, &this->renderer );

    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear( renderer );
}

Renderer::~Renderer()
{

}


void Renderer::Draw(Shader* shader)
{
    glClearColor( this->r, this->g, this->b, this->a );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->UseProgram();

    glDrawArrays(GL_TRIANGLES, 0, 3);
    // if( shader->getIndices() != nullptr)
    // {
    //     glDrawElements(GL_ELEMENT_ARRAY_BUFFER, shader->getIndices()->getLength(), GL_UNSIGNED_INT, 0);
    // }
}

void Renderer::ClearColor(float r, float g, float b, float a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}