#include "../headers/shader.h"
#include "../headers/io/filemanger.h"

BaseShader::BaseShader()
{
}

BaseShader::~BaseShader()
{
    this->DestroyShader();
}

GLuint BaseShader::CompileShader(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, 0);

    glCompileShader(shader);

    GLint compile_success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_success);

    if (compile_success == GL_FALSE)
    {
        printf("failed to compile vertex shader\n");

        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

        printf("Compilation error in %s shader : %s", type == GL_VERTEX_SHADER ? "vertex" : "fragment", strInfoLog);

        delete[] strInfoLog;
        glDeleteShader(shader);
    }

    return shader;
}

void BaseShader::Load(const char *vertexShaderSource, const char *fragmentShaderSource)
{
    program = glCreateProgram();

    printf("Shader program: %d\n", program);

    vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    if (vertexShader == 0 || fragmentShader == 0)
    {
        printf("compilation failed \n");
        glDeleteProgram(program);
    }

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    GLint link_success = 0;

    glGetProgramiv(program, GL_LINK_STATUS, &link_success);

    if (link_success == GL_FALSE)
    {
        printf("failed to link program \n");
        glDeleteProgram(program);
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    this->isCompiled = true;

    glGenVertexArrays(1, &vao);
}

void BaseShader::AddVertexBuffer(VertexBuffer *buffer)
{
    buffer->Initialize(program);
    vertexBuffers.push_back(buffer);
}

void BaseShader::AddIndexBuffer(IndexBuffer *buffer)
{
    buffer->Initialize(program);
    indexBuffer = buffer;
    length = indexBuffer->GetLength();
}

void BaseShader::UseProgram()
{
    if (this->IsCompiled())
    {
        glUseProgram(program);
        for (auto const &vb : vertexBuffers)
        {
            vb->Bind();
        }
        indexBuffer->Bind();

        for (auto it = this->uniformFloat4Lookup.begin(); it != this->uniformFloat4Lookup.end(); ++it)
        {
            float r = it->second.x;
            float g = it->second.y;
            float b = it->second.z;
            float a = it->second.w;
            glUniform4f(it->first, r, g, b, a);
        }
    }
}

void BaseShader::StopProgram()
{
    if (this->IsCompiled())
    {
        for (auto const &vb : vertexBuffers)
        {
            vb->Unbind();
        }
        indexBuffer->Unbind();
        glUseProgram(0);
    }
}

void BaseShader::DestroyShader()
{
    for (auto const &vb : vertexBuffers)
    {
        vb->DeleteBuffer();
    }
    indexBuffer->DeleteBuffer();
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(program);
}

void BaseShader::setUniform4f(char *uniform, float r, float g, float b, float a)
{
    const Vec4 v = Vec4(r, g, b, a);
    this->setUniform4fv(uniform, v);
}

void BaseShader::setUniform4fv(char *uniform, Vec4 const &v)
{
    if (!this->uniformLocationsLookup.count(uniform))
    {
        this->uniformLocationsLookup[uniform] = glGetUniformLocation(this->program, uniform);
    }
    this->uniformFloat4Lookup[this->uniformLocationsLookup[uniform]] = v;
}

const ShaderSource BaseShader::GetSourceFromPath(const char *filename)
{
    std::string source = FileManager().ReadFile(filename);

    std::string vertex_name = "VERTEX_SHADER";
    std::string fragment_name = "FRAGMENT_SHADER";

    size_t v_start = source.find(vertex_name);
    size_t f_start = source.find(fragment_name);

    std::string vertex_source = source.substr(v_start + vertex_name.size(), f_start - vertex_name.size());
    std::string fragment_source = source.substr(f_start + fragment_name.size());

    return {vertex_source, fragment_source};
};