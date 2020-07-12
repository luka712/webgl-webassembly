#pragma warning(push)
#pragma warning(disable : 4800) // conversion warning.

/**
 * Renderable -> Mesh ( init shader and geomtry ) -> Material -> Shader
 *                                                -> Geometry -> IB
 *                                                            -> VB[]
 */

#include <stdlib.h>
#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <stdio.h>

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

void Initialize();
void draw();

Renderer *renderer;
BaseShader *shader;

int main()
{
    Initialize();

    renderer = new Renderer();
    auto quadMesh = new QuadMesh();
    shader = new BaseShader();

    // request animation draw from javascript
    emscripten_set_main_loop(draw, 0, 0);
}

void Initialize()
{
    // 1. First initialize render.
    renderer = new Renderer();

    // 2. After renderer scene manager is to be initialized.
    SceneManager::GetInstance()->Initialize();
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
    // shader->SetUniform4f(uniformName, r, g, b, a);
    // glm::mat4 projection = glm::perspective(glm::radians(60.0f), 800.0f / 600.f, 0.0f, 100.0f);
    // shader->SetMatrix4("u_projection", projection);
    // glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 15.0f);
    // glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    // glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    // glm::mat4 view = glm::lookAt(cameraPos, cameraFront, cameraUp);
    // shader->SetMatrix4("u_view", view);
    // glm::mat4 transform = glm::mat4(1.0);
    // shader->SetMatrix4("u_transform", transform);
}

extern "C" bool create_shader_material(const char *vertexShaderSource, const char *fragmentShaderSource)
{
    // shader->UseProgram();
    // shader->Initialize(vertexShaderSource, fragmentShaderSource);
    // return true;
}

extern "C" void load_indices_data(unsigned int *data, int length)
{
    // shader->UseProgram();
    // auto buffer = new IndexBuffer(data, length);
    // shader->AddIndexBuffer(buffer);
}

extern "C" void load_attribute_data(float *data, int size, int length, char *attributeName)
{
    // auto buffer = new VertexBuffer(attributeName, size, data, length);
    // shader->AddVertexBuffer(buffer);
}

extern "C" void test(Uint8 *data)
{
    jsFunction(data[0]);
    jsFunction(data[1]);
    jsFunction(data[2]);
}

extern "C" void set_shader_matrix4(char *name, float *matrix)
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

void MoveCurrentCamera(glm::vec3 pos)
{
    SceneManager::GetInstance()->GetCurrentScene()->GetCamera()->Move(pos);
}

EMSCRIPTEN_BINDINGS(camera)
{
}

QuadMesh *CreateQuadMesh()
{
}

glm::vec3 *createVector(float x, float y, float z)
{
    return new glm::vec3(x, y, z);
}


EMSCRIPTEN_BINDINGS(mesh)
{
    //  value_object<glm::vec3>("vec3")
    //     .field("x", &glm::vec3::x)
    //     .field("y", &glm::vec3::y)
    //     .field("z", &glm::vec3::z);

    function("MoveCurrentCamera", &MoveCurrentCamera, allow_raw_pointers());

    // class_<glm::vec3>("Vec3")
    //     .constructor(&createVector, allow_raw_pointers())
    //     .property("x", optional_override([](glm::vec3 &self) -> float {
    //                   return self.x;
    //               }));

    auto overrideGetPosition = optional_override([](Transform &self) {
        return self.GetPosition();
    });

    class_<Transform>("Transform")
        .constructor()
        .function("getPosition", overrideGetPosition, allow_raw_pointers());

    // class_<VertexBuffer>("VertexBuffer");
    // class_<IndexBuffer>("IndexBuffer");

    class_<Mesh>("Mesh")
        .constructor();

    auto overrideGetTransform = optional_override([](QuadMesh &self) {
        return self.GetTransform();
    });

    class_<QuadMesh, base<Mesh>>("QuadMesh")
        .constructor()
        .function("getTransform", overrideGetTransform, allow_raw_pointers())
        .function("translate", &QuadMesh::Translate, allow_raw_pointers());

    function("createQuadMesh", &CreateQuadMesh, allow_raw_pointers());
}

// shader operations
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
