
#include "../shader.h"

class Material
{
protected:
    unsigned long id;
    BaseShader *shader;

public:
    Material();
    BaseShader *GetShader() const { return shader; }
};

class ColorMaterial : public Material
{
public:
    ColorMaterial();
};