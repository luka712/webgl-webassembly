#include "../../headers/scene/scenemanager.h"
#include "../../headers/scene/scene.h"

SceneManager::SceneManager(){}

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
    printf("Creating scene manager instance.\n");
    printf("%p\n", &SceneManager::instance);
    if (!SceneManager::initialized)
    {
        SceneManager::initialized = true;
        printf("Scene manager instance trying to create.\n");
        SceneManager::instance = new SceneManager();
        printf("Scene manager instance created.\n");
    }
    printf("%p\n", &SceneManager::instance);

    return SceneManager::instance;
}

void SceneManager::Initialize()
{
    this->current = new Scene();
    printf("Scene created\n");
    this->current->SetCamera(new PerspectiveCamera());
    printf("Camera set\n");
    this->current->AddMaterial(new ColorMaterial());
    printf("Material set\n");
    this->current->AddMesh(new QuadMesh());
    printf("Mesh set\n");
}

void SceneManager::AddScene(Scene *scene)
{
    scenes->push_back(scene);
}

void SceneManager::RemoveScene(Scene *scene)
{
    scenes->remove(scene);
}
