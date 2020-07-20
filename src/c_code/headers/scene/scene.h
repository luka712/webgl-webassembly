#pragma once

#include <list>
#include "../camera/camera.h"
#include "../mesh/mesh.h"


class Scene
{
private:
    std::list<std::shared_ptr<Mesh>> *meshes;
    std::list<std::shared_ptr<Material>> *materials;
    std::shared_ptr<Camera> camera;

public:
    Scene();
    ~Scene();

    std::list<std::shared_ptr<Mesh>> *GetMeshes() { return meshes; };
    std::list<std::shared_ptr<Material>> *GetMaterials() { return materials; }

    std::shared_ptr<Camera> GetCamera() { return camera; }
    void SetCamera(std::shared_ptr<Camera> cam) { this->camera = cam; }

    void AddMesh(std::shared_ptr<Mesh> mesh);
    void RemoveMesh(std::shared_ptr<Mesh> mesh);
    void AddMaterial(std::shared_ptr<Material> material);
    void RemoveMaterial(std::shared_ptr<Material> material);
};
