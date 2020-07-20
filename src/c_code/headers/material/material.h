
#include "../shader.h"

class Material
{
protected:
    unsigned long id;
    std::shared_ptr<BaseShader> shader;

public:
    Material();
    std::shared_ptr<BaseShader> GetShader() const { return shader; }
};

class ColorMaterial : public Material
{
public:
    ColorMaterial();
};