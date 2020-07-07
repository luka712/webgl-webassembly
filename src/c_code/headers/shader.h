#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include "./glattribute.h"
#include "./glindices.h"

class Shader 
{
    private:
        std::map<std::string, GLint> uniformLocationsLookup;
        std::map<GLint, float[4]> uniformFloat4Lookup;
        GLuint vertexShader;
        GLuint fragmentShader;
        GLuint program;
        bool isCompiled;
        GLIndices *indices = nullptr;
        GLuint elementBuffer;
        std::vector<GLuint> arrayBuffers;
        int buffersCount = 1;
        GLuint CompileShader(const GLenum type, const char *source);
      

    public:
        Shader();
        ~Shader();
        bool IsCompiled()
        {
            return isCompiled;
        }
        GLIndices* getIndices() const 
        {
            return this->indices;
        }
        void Load(const char* vertexShaderSource, const char* fragmentShaderSource);
        void LoadAttribute(GLAttribute* attr);
        void LoadIndices(GLIndices* indices);
        void DestroyShader();
        void UseProgram();
        void StopProgram();
        void setUniformf4(char *uniform, float r, float g, float b, float a);
};