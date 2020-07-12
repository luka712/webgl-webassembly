#pragma once

#include <list>
#include "../camera/camera.h"
#include "../mesh/mesh.h"

class Scene
{
private:
    std::list<Mesh *> *meshes;
    std::list<Material *> *materials;
    Camera *camera;

public:
    Scene();
    ~Scene();

    std::list<Mesh *> *GetMeshes() { return meshes; };
    std::list<Material *> *GetMaterials() { return materials; }

    Camera *GetCamera() { return camera; }
    void SetCamera(Camera *cam) { this->camera = cam; }

    void AddMesh(Mesh *mesh);
    void RemoveMesh(Mesh *mesh);
    void AddMaterial(Material *material);
    void RemoveMaterial(Material *material);
};
