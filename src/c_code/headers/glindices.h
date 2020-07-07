#include <GLES3/gl3.h>

class GLIndices
{

private:
    GLuint *data;
    int length;

public:
    GLIndices(GLuint* data,int length);

    int getLength() const { return this->length; };
    GLuint *getData() const { return this->data; };
};