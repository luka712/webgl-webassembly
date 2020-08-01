
#include "shader/shader.h"

class Material
{
protected:
    std::string id;
    std::shared_ptr<BaseShader> shader;

public:
    Material(std::string id);
    std::shared_ptr<BaseShader> GetShader() const { return shader; }
};

class ColorMaterial : public Material
{
public:
    ColorMaterial();
};