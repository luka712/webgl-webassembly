struct Vec3
{
    float x;
    float y;
    float z;

    Vec3(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

struct Vec4
{
    float x;
    float y;
    float z;
    float w;

    Vec4(){}

    Vec4(float x, float y, float z, float w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
};

struct Color
{
    float r;
    float g;
    float b;
    float a;

    Color() {}

    Color(float r, float g, float b, float a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    Vec4 ToVector()
    {
        return Vec4(r, g, b, a);
    }
};
