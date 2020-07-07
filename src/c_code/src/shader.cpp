#include "../headers/shader.h"

Shader::Shader()
{

}

Shader::~Shader()
{
    this->DestroyShader();
}

GLuint Shader::CompileShader(GLenum type, const char *source)
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


void Shader::Load(const char* vertexShaderSource, const char* fragmentShaderSource)
{
    program = glCreateProgram();
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
}


void Shader::LoadAttribute(GLAttribute* attr)
{
    GLuint vertexBuffer;
    GLint attributeLoc = glGetAttribLocation(this->program, attr->getName());

    glGenBuffers(this->buffersCount++, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * attr->getLength(), attr->getData(), GL_STATIC_DRAW);

    if(vertexBuffer <= 0){
        printf("Vertex buffer not bound %d\n", vertexBuffer);
    }

    glEnableVertexAttribArray(attributeLoc);
    glVertexAttribPointer(attributeLoc, attr->getSize(), GL_FLOAT, GL_FALSE, 0, 0);

    arrayBuffers.push_back(vertexBuffer);
}

void Shader::LoadIndices(GLIndices* indices)
{
    glGenBuffers(this->buffersCount++, &this->elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->getLength() * sizeof(unsigned int), indices->getData(), GL_STATIC_DRAW);

    if(this->elementBuffer <= 0){
        printf("Element buffer not bound %d\n", this->elementBuffer);
    }
}



void Shader::UseProgram()
{
    if(this->IsCompiled())
    {
        glUseProgram(program);      

        for (std::map<GLint, float[4]>::iterator it = this->uniformFloat4Lookup.begin(); it != this->uniformFloat4Lookup.end(); ++it)
        {
            float r = it->second[0];
            float g = it->second[1];
            float b = it->second[2];
            float a = it->second[3];
            glUniform4f(it->first, r, g, b, a);
        }

    }
}

void Shader::StopProgram()
{
    if(this->IsCompiled())
    {
        glUseProgram(0);
    }
}

void Shader::DestroyShader()
{
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(program);
}

void  Shader::setUniformf4(char *uniform, float r, float g, float b, float a)
{
    if(!this->uniformLocationsLookup.count(uniform))
    {
        this->uniformLocationsLookup[uniform] = glGetUniformLocation(this->program, uniform);
        this->uniformFloat4Lookup[this->uniformLocationsLookup[uniform]][0] = r;
    }
    this->uniformFloat4Lookup[this->uniformLocationsLookup[uniform]][0] = r;
    this->uniformFloat4Lookup[this->uniformLocationsLookup[uniform]][1] = g;
    this->uniformFloat4Lookup[this->uniformLocationsLookup[uniform]][2] = b;
    this->uniformFloat4Lookup[this->uniformLocationsLookup[uniform]][3] = a;
}