#pragma once 

#include <stdio.h>
#include <vector>
#include <map>
#include <list>
#include <string>

#include "../../../include/glm/mat4x4.hpp"
#include "../../../include/glm/matrix.hpp"
#include "../../../include/glm/ext.hpp"
#include "../headers/constants.h"
#include "../headers/buffers/buffers.h"

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
    std::list<VertexBuffer *> vertexBuffers;

    std::map<std::string, GLint> uniformLocationsLookup;
    std::map<GLint, glm::mat4> uniformMat4Lookup;
    std::map<GLint, glm::vec4> uniformFloat4Lookup;

    int length;
    bool isCompiled;

    GLuint CompileShader(const GLenum type, const char *source);

public:
    BaseShader();
    ~BaseShader();

    GLuint GetProgram() const { return program; }

    bool IsCompiled() const { return isCompiled; }
    int GetLength() const { return length; }

    IndexBuffer *GetIndexBuffer() const { return indexBuffer; }

    void Compile(const char *vertexShaderSource, const char *fragmentShaderSource);

    void AddVertexBuffer(VertexBuffer *vertexBuffer);
    void AddIndexBuffer(IndexBuffer *indexBuffer);
    
    void UseProgram();
    void StopProgram();
    void DestroyShader();

    void SetUniform4f(char *uniform, float r, float g, float b, float a);
    void SetUniform4fv(char *uniform, glm::vec4 const &vec);
    void SetMatrix4(const char *uniform, glm::mat4 const matrix);

    static const ShaderSource GetSourceFromPath(const char *filepath);
};

class ColorShader : public BaseShader
{

public:
    ColorShader();
    ~ColorShader();
    void SetColor(glm::vec4 const &vec);
};
