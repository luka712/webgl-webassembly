#include <stdexcept>

#include "../../headers/scene/scene.h"

Scene::Scene(std::string id)
{
    this->id = id;
}

Scene::~Scene()
{
    for (auto const &[key, val] : meshes)
    {
        delete &key;
        delete &val;
    }
}

void Scene::AddObject(SceneObject* obj)
{
    objects.emplace_back(std::shared_ptr<SceneObject>(obj));
}

void Scene::AddMesh(Mesh* mesh, bool overrideExisting)
{
    auto exists = meshes.find(mesh->id) != meshes.end();
    if (!exists || overrideExisting)
    {
        auto meshPtr = std::shared_ptr<Mesh>(mesh);
        meshes.emplace(mesh->id, meshPtr);
        // conditional log
        // LOG_FORMAT("Mesh with id %s already added!", mesh->id);
    }
}

void Scene::RemoveMesh(std::string id)
{
    this->meshes.erase(id);
}

EMSCRIPTEN_BINDINGS(Scene)
{
    emscripten::class_<Scene>("Scene")
        .smart_ptr_constructor("Scene", &std::make_shared<Scene, std::string>)
        .function("GetCamera", &Scene::GetCamera, emscripten::allow_raw_pointers());
}