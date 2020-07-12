
#include "./scene.h"

class Scene;

class SceneManager
{
private:
    // static SceneManager *instance;
    Scene *current;
    std::list<Scene *> *scenes;
    static SceneManager *instance;
    static bool initialized;

public:
    SceneManager();
    ~SceneManager();
    static SceneManager *GetInstance();
    void Initialize();
    void AddScene(Scene *scene);
    void RemoveScene(Scene *scene);
    Scene *GetCurrentScene() { return current; }
};


