#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <list>
#include "../../headers/scene/scenemanager.h"


class Renderer
{
private:
    static Renderer *instance;
    static bool initialized;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_GLContext gl_context;
    Camera *camera;
    std::list<BaseShader *> shaders;

    float r = 1;
    float g = 0;
    float b = 0;
    float a = 1;

public:
    ~Renderer();
    static Renderer *GetInstance();
    void Initialize(const int width, const int height);
    void AddShader(BaseShader *shader);
    void Draw();
    void ClearColor(float r, float g, float b, float a);
};