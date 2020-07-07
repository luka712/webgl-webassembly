class GLAttribute
{

private:
    char *name;
    float *data;
    int size;
    int length;

public:
    GLAttribute( char* name,  float* data, int size, int length);

    char* getName() const { return this->name; };
    float *getData() const { return this->data; };
    int getSize() const { return this->size; };
    int getLength() const { return this->length; }
};