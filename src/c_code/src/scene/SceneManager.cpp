#include "../../headers/scene/scenemanager.h"
#include "../../headers/scene/scene.h"

SceneManager::SceneManager() {}

SceneManager::~SceneManager()
{
    // for (auto scn = scenes.begin(); scn != scenes.end(); ++scn)
    // {
    //     delete &scn;
    // }
}

SceneManager *SceneManager::instance = 0;
bool SceneManager::initialized = false;

SceneManager *SceneManager::GetInstance()
{
    if (!SceneManager::initialized)
    {
        SceneManager::initialized = true;
        SceneManager::instance = new SceneManager();
    }

    return SceneManager::instance;
}

void SceneManager::Initialize()
{
    DEBUG_PRINT("Setting up main scene.");
    this->current = new Scene();
    this->current->SetCamera(new PerspectiveCamera());
    this->current->AddMaterial(new ColorMaterial());
    DEBUG_PRINT("Main scene set up.");
}

void SceneManager::AddScene(Scene *scene)
{
    scenes->push_back(scene);
}

void SceneManager::RemoveScene(Scene *scene)
{
    scenes->remove(scene);
}
