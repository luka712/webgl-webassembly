#pragma once


#include <map>
#include "../camera/camera.h"
#include "../mesh/mesh.h"
#include "../scene/sceneobject.h"


class Scene : public IId
{
private:
    std::map<std::string, std::shared_ptr<Mesh>> meshes;
    std::shared_ptr<BaseCamera> camera;
    std::vector<std::shared_ptr<SceneObject>> objects;

public:
    Scene(std::string id);
    ~Scene();

    std::vector<std::shared_ptr<SceneObject>> GetObjects() const { return objects; }
    void AddObject(SceneObject *obj);

    std::map<std::string, std::shared_ptr<Mesh>> GetMeshes() { return meshes; };

    std::shared_ptr<BaseCamera> GetCamera() { return camera; }
    void SetCamera(std::shared_ptr<BaseCamera> cam) { this->camera = cam; }

    void AddMesh(Mesh* mesh, bool overrideExisting = false);
    void RemoveMesh(std::string id);
};

