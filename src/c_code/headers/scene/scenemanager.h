
#include "./scene.h"
#include "../event/event.h"

class Scene;

class SceneManager
{
private:
    static std::shared_ptr<SceneManager> instance;
    static bool initialized;

    std::shared_ptr<EventDispatcher> dispatcher;
    std::shared_ptr<Scene> current;
    std::list<std::shared_ptr<Scene>> *scenes;

public:
    SceneManager();
    ~SceneManager();
    static std::shared_ptr<SceneManager> GetInstance();
    void Initialize();
    void AddScene(std::shared_ptr<Scene> scene);
    void RemoveScene(std::shared_ptr<Scene> scene);
    std::shared_ptr<Scene> GetCurrentScene() { return current; }
    std::shared_ptr<EventDispatcher> GetEventDispatcher() const { return dispatcher; }
};
