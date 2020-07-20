#include <stdexcept>

#include "../../headers/scene/scene.h"

Scene::Scene()
{
    meshes = new std::list<std::shared_ptr<Mesh>>;
    materials = new std::list<std::shared_ptr<Material>>;
}

Scene::~Scene()
{
    for (auto m = meshes->begin(); m != meshes->end(); ++m)
    {
        delete &m;
    }

    delete meshes;
}

void Scene::AddMesh(std::shared_ptr<Mesh> mesh)
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

void Scene::RemoveMesh(std::shared_ptr<Mesh> mesh)
{
    this->meshes->remove(mesh);
}

void Scene::AddMaterial(std::shared_ptr<Material> material)
{
    this->materials->push_back(material);
}

void Scene::RemoveMaterial(std::shared_ptr<Material> material)
{
    this->materials->remove(material);
}



EMSCRIPTEN_BINDINGS(Scene)
{
    emscripten::class_<Scene>("Scene")
        .smart_ptr_constructor("Scene", &std::make_shared<Scene>)
        .function("GetCamera", &Scene::GetCamera, emscripten::allow_raw_pointers());
}