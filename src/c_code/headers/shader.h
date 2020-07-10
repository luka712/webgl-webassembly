#include <stdio.h>
#include <vector>
#include <map>
#include <list>
#include <string>
#include "./math/math.h"
#include "./glattribute.h"
#include "./glindices.h"
#include "./buffers/buffers.h"
#include "./constants.h"

struct ShaderSource
{
    std::string vertexSource;
    std::string fragmentSource;
};

class BaseShader
{
private:
    GLuint program;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint vao;
    IndexBuffer *indexBuffer;
    std::list<VertexBuffer*> vertexBuffers;

    std::map<std::string, GLint> uniformLocationsLookup;
    std::map<GLint, Vec4> uniformFloat4Lookup;

    int length;
    bool isCompiled;

    GLuint CompileShader(const GLenum type, const char *source);

public:
    BaseShader();
    ~BaseShader();

    bool IsCompiled()  
    {
        return isCompiled;
    }

    int GetLength() const { return length; }

    IndexBuffer* GetIndexBuffer() const { return indexBuffer; }

    void Load(const char *vertexShaderSource, const char *fragmentShaderSource);
    void AddVertexBuffer(VertexBuffer *vertexBuffer);
    void AddIndexBuffer(IndexBuffer *indexBuffer);
    void DestroyShader();
    void UseProgram();
    void StopProgram();
    void setUniform4f(char *uniform, float r, float g, float b, float a);
    void setUniform4fv(char *uniform, Vec4 const &vec);
    static const ShaderSource GetSourceFromPath(const char *filepath);
};

class ColorShader : public BaseShader
{
    public:
        ColorShader();
        ~ColorShader();
        void SetColor(Vec4 const &vec);
};
