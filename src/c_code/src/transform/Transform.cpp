
#include "../../headers/transform/transform.h"

void Transform::ApplyTransformations()
{
    auto translate = glm::scale(glm::mat4(1.0f), glm::vec3(scale->x, scale->y, scale->z));
    auto rotateX = glm::rotate(glm::mat4(1.0f), rotation->x, glm::vec3(1.0f, 0.0f, 0.0f));
    auto rotateY = glm::rotate(glm::mat4(1.0f), rotation->y, glm::vec3(0.0f, 1.0f, 0.0f));
    auto rotateZ = glm::rotate(glm::mat4(1.0f), rotation->z, glm::vec3(0.0f, 0.0f, 1.0f));
    auto scl = glm::translate(glm::mat4(1.0f), glm::vec3(position->x, position->y, position->z));

    transform = scl * rotateX * rotateY * rotateZ * translate;
};

struct Vec3
{
    float x;
    float y;
    float z;
};

EMSCRIPTEN_BINDINGS(Vec3)
{
    emscripten::value_object<Vec3>("Vec3")
        .field("x", &Vec3::x)
        .field("y", &Vec3::y)
        .field("z", &Vec3::z);
}

EMSCRIPTEN_BINDINGS(Transform)
{
    emscripten::class_<Transform>("Transform")
        .constructor()
        .function("GetPosition", emscripten::optional_override([](Transform &self) -> Vec3 {
                      return {self.position->x, self.position->y, self.position->z};
                  }),
                  emscripten::allow_raw_pointers())
        .function("SetPosition", emscripten::optional_override([](Transform &self, Vec3 v) -> void {
                      self.position->x = v.x;
                      self.position->y = v.y;
                      self.position->z = v.z;
                  }),
                  emscripten::allow_raw_pointers());

    //         .function("GetScale", &Transform::GetScale, emscripten::allow_raw_pointers())
    //         .function("GetRotation", &Transform::GetRotation, emscripten::allow_raw_pointers())
    //         .function("SetPosition", &Transform::SetPosition, emscripten::allow_raw_pointers())
    //         .function("SetScale", &Transform::SetScale, emscripten::allow_raw_pointers())
    //         .function("SetRotation", &Transform::SetRotation, emscripten::allow_raw_pointers());
}
