#pragma once

#include "../scene/sceneobject.h"

class Component : public IId
{
public:
    SceneObject *sceneObject;
    virtual void Initialize() {}
    virtual void Update() {}
    virtual void Render() {}
};

