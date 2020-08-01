#pragma once

#include <memory>
#include <vector>
#include <string>
#include "../../../../include/glm/vec3.hpp"

#include "../id.h"

class Scene;
class Component;
class Mesh;
class TransformComponent;

class SceneObject : public IId
{
    private:
        /** reference to scene this object belongs to */
        Scene *scene;
        /** all the components held by this scene object. Use shared pointer here only */
        std::vector<std::shared_ptr<Component>> components;

    public:
        bool isActive;
        SceneObject *parent;
        TransformComponent *transform;
        Mesh *mesh;

        SceneObject();
        SceneObject(Scene *scene);
        SceneObject(std::string id, Scene *scene);

        void Translate(glm::vec3 translate);
        void Rotate(glm::vec3 rotation);
        void Scale(glm::vec3 scale);

        Component* AddComponent(Component *component);
};