#pragma warning(push)
#pragma warning(disable : 4800) // conversion warning.

#include <stdlib.h>
#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <stdio.h>

#include "../../include/glm/mat4x4.hpp"
#include "../../include/glm/matrix.hpp"
#include "../../include/glm/ext.hpp"
#include "./headers/io/filemanger.h"
#include "./headers/renderer.h"

using namespace emscripten;

// Example of calling of js function
EM_JS(void, jsFunction, (float n), {
    console.log(n);
});

struct vec2
{
    int x;
    int y;
};

void draw();

Renderer *renderer;
BaseShader *shader;
ColorShader *colorShader;

int main()
{
    renderer = new Renderer();
    shader = new BaseShader();
    colorShader = new ColorShader();

    // request animation draw from javascript
    emscripten_set_main_loop(draw, 0, 0);

    renderer->AddShader(colorShader);
    renderer->AddShader(shader);
}

void draw()
{
    renderer->Draw();
}

// extern "C" prevents C++ compiler name mangling
extern "C" void clear_color(const float r, const float g, const float b, const float a)
{
    renderer->ClearColor(r, g, b, a);
}

extern "C" void geometry_color(char *uniformName, const float r, const float g, const float b, const float a)
{
    shader->SetUniform4f(uniformName, r, g, b, a);
        glm::mat4 orthographic = glm::ortho(0.f, 1.f, 0.75f, 0.f, 0.0f, 100.0f);
    shader->SetMatrix4("u_projection", orthographic);
}

extern "C" bool create_shader_material(const char *vertexShaderSource, const char *fragmentShaderSource)
{
    shader->UseProgram();
    shader->Load(vertexShaderSource, fragmentShaderSource);
    return true;
}

extern "C" void load_indices_data(unsigned int *data, int length)
{
    shader->UseProgram();
    auto buffer = new IndexBuffer(data, length);
    shader->AddIndexBuffer(buffer);
}

extern "C" void load_attribute_data(float *data, int size, int length, char *attributeName)
{
    auto buffer = new VertexBuffer(attributeName, size, data, length);
    shader->AddVertexBuffer(buffer);
}

extern "C" void test(Uint8 *data)
{
    jsFunction(data[0]);
    jsFunction(data[1]);
    jsFunction(data[2]);
}

extern "C" void set_shader_matrix4(char* name, float* matrix)
{
    // TODO: implement setting up of matrix from JS code
    glm::mat4 orthographic = glm::ortho(0.f, 800.f, 600.f, 0.f, 0.1f, 100.0f);
    shader->SetMatrix4("u_projection", orthographic);
}

#pragma region Exports

extern "C" const char *read_file(const char *filename)
{
    return FileManager().ReadFile(filename).c_str();
}

const ShaderSource GetShaderSourceFromPath(const char *filename)
{
    return BaseShader::GetSourceFromPath(filename);
}

EMSCRIPTEN_BINDINGS(shader)
{
    value_object<ShaderSource>("ShaderSource")
        .field("vertexSource", &ShaderSource::vertexSource)
        .field("fragmentSource", &ShaderSource::fragmentSource);

    function("GetShaderSourceFromPath", optional_override([](const std::string s) {
                 return GetShaderSourceFromPath(s.c_str());
             }),
             allow_raw_pointers());
}

// Export File Manager
EMSCRIPTEN_BINDINGS(export_file_manager)
{
    auto overrideReadFile = optional_override([](FileManager &self, const std::string &s) {
        return self.ReadFile(s.c_str());
    });

    class_<FileManager>("FileManager")
        .constructor()
        // for raw pointers do an override
        .function("readFile", overrideReadFile, allow_raw_pointers());
}
#pragma endregion
