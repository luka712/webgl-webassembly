#include <stdexcept>

#include "../../headers/scene/scene.h"

Scene::Scene()
{
    meshes = new std::list<Mesh *>;
    materials = new std::list<Material *>;
}

Scene::~Scene()
{
    for (auto m = meshes->begin(); m != meshes->end(); ++m)
    {
        delete &m;
    }

    delete meshes;
}

void Scene::AddMesh(Mesh *mesh)
{
    this->meshes->push_back(mesh);
    if(!mesh->GetMaterial())
    {
        auto mat = materials->front();
        if(mat)
        {
            mesh->SetMaterial(mat);
        }
        else 
        {
            printf("Scene has no material definition defined. Make sure that scene has at least one material definition before creating the material.\n");
            //throw std::runtime_error(std::string("Scene has no material definition defined. Make sure that scene has at least one material definition before creating the material."));
        }
    }
}

void Scene::RemoveMesh(Mesh *mesh)
{
    this->meshes->remove(mesh);
}

void Scene::AddMaterial(Material *material)
{
    this->materials->push_back(material);
}

void Scene::RemoveMaterial(Material *material)
{
    this->materials->remove(material);
}
