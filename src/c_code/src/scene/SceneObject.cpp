#include <iostream>

#include "../../headers/scene/sceneobject.h"
#include "../../headers/component/transformcomponent.h"
#include "../../headers/scene/scenemanager.h"

SceneObject::SceneObject()
{
    this->scene = SceneManager::GetInstance()->GetCurrentScene();
    this->scene->AddObject(this);
    this->id = "";
}

SceneObject::SceneObject(Scene *scene)
{
    this->scene = scene;
    this->scene->AddObject(this);
    this->id = "";
}

SceneObject::SceneObject(std::string id, Scene *scene)
{
    this->id = id;
    this->scene->AddObject(this);
    this->scene = scene;
}

Component *SceneObject::AddComponent(Component *component)
{
    std::shared_ptr<Component> sc(component);
    sc->sceneObject = this;
    components.emplace_back(sc);
    sc->Initialize();

    if (component->type == ObjectType::TransformType)
    {
        transform = (TransformComponent *)component;
    }

    if(component->type == ObjectType::MeshType)
    {
        mesh = (Mesh *)component;
    }

    return component;
}

void SceneObject::Translate(glm::vec3 t)
{
    transform->position->x = t.x;
    transform->position->y = t.y;
    transform->position->z = t.z;
}

void SceneObject::Rotate(glm::vec3 r)
{
    transform->rotation->x = r.x;
    transform->rotation->y = r.y;
    transform->rotation->z = r.z;
}

void SceneObject::Scale(glm::vec3 s)
{
    transform->scale->x = s.x;
    transform->scale->y = s.y;
    transform->scale->z = s.z;
}

EMSCRIPTEN_BINDINGS(SceneObject)
{
    emscripten::class_<SceneObject, emscripten::internal::NoBaseClass>("SceneObject")   
        .smart_ptr_constructor("SceneObject", &std::make_shared<SceneObject>)
        .function("translate", &SceneObject::Translate, emscripten::allow_raw_pointers())
        .function("scale", &SceneObject::Scale, emscripten::allow_raw_pointers())
        .function("rotate", &SceneObject::Rotate, emscripten::allow_raw_pointers());
    // .property("transform", emscripten::optional_override([](SceneObject &self) -> TransformComponent* {
    //               return self.transform;
    //           }), emscripten::allow_raw_pointers());
}