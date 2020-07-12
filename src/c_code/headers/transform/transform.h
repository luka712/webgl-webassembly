#include "../../../../include/glm/glm.hpp"
#include "../../../../include/glm/ext.hpp"

class Transform
{
public:
    glm::mat4 transform;
    glm::vec3 *position;
    Transform()
    {
        transform = glm::mat4(1.0f);
        position = new glm::vec3(0.0f);
    }
    glm::vec3 *GetPosition() { return position; }
    void SetPosition(glm::vec3 *v) { position = v; }
    void ApplyTransformations()
    {
        transform = glm::translate(glm::mat4(1.0f), glm::vec3(position->x, position->y, position->z));
    };
};