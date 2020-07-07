#pragma warning(push)
#pragma warning(disable : 4800) // conversion warning.


#include <stdlib.h>
#include <emscripten.h>
#include <stdio.h>

#include "./headers/renderer.h"

// Example of calling of js function
EM_JS(void, jsFunction, (float n), {
    console.log(n);
});

void draw();

Renderer* renderer;
Shader* shader;

int main()
{
    renderer = new Renderer();
    shader = new Shader();

    // request animation draw from javascript
    emscripten_set_main_loop(draw, 0, 0);
}

void draw()
{
    renderer->Draw(shader);
}

// extern "C" prevents C++ compiler name mangling
extern "C" void clear_color(const float r, const float g,const float b,const float a)
{
    renderer->ClearColor(r, g, b, a);
}

extern "C" void geometry_color(char* uniformName, const float r, const float g,const float b,const float a)
{
    shader->setUniformf4(uniformName, r, g, b, a);
}

extern "C" bool create_shader_material(const char *vertexShaderSource, const char *fragmentShaderSource)
{
    shader->Load(vertexShaderSource, fragmentShaderSource);
    return true;
}

extern "C" void load_indices_data(unsigned int* data, int length)
{
    shader->LoadIndices(new GLIndices(data, length));
}

extern "C" void load_attribute_data(float* data, int size, int length, char* attributeName)
{
    shader->LoadAttribute( new GLAttribute(attributeName, data, size, length));
}

extern "C" void test(Uint8* data)
{
    jsFunction(data[0]);
    jsFunction(data[1]);
    jsFunction(data[2]);
}

