#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <list>
#include "../headers/shader.h"


class Renderer
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    Camera *camera;
    std::list<BaseShader *> shaders;

    float r = 1;
    float g = 0;
    float b = 0;
    float a = 1;

public:
    Renderer();
    Renderer(int width, int height);
    ~Renderer();
    void AddShader(BaseShader *shader);
    void Draw();
    void ClearColor(float r, float g, float b, float a);
};