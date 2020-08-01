#pragma once

#include <string>

enum ObjectType
{
    None = 0,
    MeshType,
    TransformType
};

class IId 
{
    public:
        std::string id;
        ObjectType type;
};