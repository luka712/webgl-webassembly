#include "../headers/glattribute.h"

GLAttribute::GLAttribute( char* name,  float* data, int size, int length)
{
    this->name = name;
    this->data = data;
    this->size = size;
    this->length = length;
}
