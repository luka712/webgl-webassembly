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

std::shared_ptr<SceneManager> SceneManager::instance = 0;
bool SceneManager::initialized = false;

std::shared_ptr<SceneManager> SceneManager::GetInstance()
{
    if (!SceneManager::initialized)
    {
        SceneManager::initialized = true;
        SceneManager::instance = std::make_shared<SceneManager>();
    }

    return SceneManager::instance;
}

void SceneManager::Initialize()
{
    LOG("Setting up main scene.");

    this->dispatcher = std::make_shared<EventDispatcher>();

    this->current = std::make_shared<Scene>();

    auto camera = std::make_shared<PerspectiveCamera>();
    this->current->SetCamera(camera);

    auto material = std::make_shared<ColorMaterial>();
    this->current->AddMaterial(material);
    
    auto mesh = std::make_shared<CubeMesh>();
    this->current->AddMesh(mesh);

    this->dispatcher->dispatchEvent(EventType::SceneManagerInitialized, current);

    LOG("Main scene set up.");
}

void SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
    scenes->push_back(scene);
}

void SceneManager::RemoveScene(std::shared_ptr<Scene> scene)
{
    scenes->remove(scene);
}

EMSCRIPTEN_BINDINGS(SceneManager)
{

    emscripten::class_<SceneManager>("SceneManager")
         .smart_ptr_constructor("SceneManager", &std::make_shared<SceneManager>)
        .class_function("GetInstance", &SceneManager::GetInstance, emscripten::allow_raw_pointers())
        .function("GetCurrentScene", &SceneManager::GetCurrentScene, emscripten::allow_raw_pointers());
}