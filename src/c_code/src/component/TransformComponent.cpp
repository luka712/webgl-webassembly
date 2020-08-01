#include "../../headers/component/transformcomponent.h"
#include "../../../../include/glm/gtc/matrix_transform.hpp"

TransformComponent::TransformComponent()
{

    id = "transform_component";
    type = ObjectType::TransformType;
    position = std::make_shared<glm::vec3>(0.0f, 0.0f, -3.0f);
    rotation = std::make_shared<glm::vec3>(0.0f, 0.0f, 0.0f);
    scale = std::make_shared<glm::vec3>(1.0f, 1.0f, 1.0f);
}

TransformComponent::TransformComponent(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl)
{
    id = "transform_component";
    type = ObjectType::TransformType;
    position = std::make_shared<glm::vec3>(pos.x, pos.y, pos.z);
    rotation = std::make_shared<glm::vec3>(rot.x, rot.y, rot.z);
    scale = std::make_shared<glm::vec3>(scl.x, scl.y, scl.z);
}

void TransformComponent::Update()
{
    transform = glm::mat4(1.0f);
    glm::scale(transform, glm::vec3(position->x, position->y, position->z));
    auto rotateX = glm::rotate(transform, rotation->x, glm::vec3(1.0f, 0.0f, 0.0f));
    auto rotateY = glm::rotate(transform, rotation->y, glm::vec3(0.0f, 1.0f, 0.0f));
    auto rotateZ = glm::rotate(transform, rotation->z, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::translate(transform, glm::vec3(scale->x, scale->y, scale->z));
}

EMSCRIPTEN_BINDINGS(vec3)
{
    emscripten::value_object<glm::vec3>("vec3")
        .field("x", &glm::vec3::x)
        .field("y", &glm::vec3::y)
        .field("z", &glm::vec3::z);

//     emscripten::class_<glm::vec3>("Vec3")
//         .property("x", emscripten::optional_override([](glm::vec3 &self) -> float {
//                       return self.x;
//                   }),
//                   emscripten::optional_override([](glm::vec3 &self, float v) {
//                       self.x = v;
//                   }))
//         .property("y", emscripten::optional_override([](glm::vec3 &self) -> float {
//                       return self.y;
//                   }),
//                   emscripten::optional_override([](glm::vec3 &self, float v) {
//                       self.y = v;
//                   }))
//         .property("z", emscripten::optional_override([](glm::vec3 &self) -> float {
//                       return self.z;
//                   }),
//                   emscripten::optional_override([](glm::vec3 &self, float v) {
//                       self.z = v;
//                   }));
}

EMSCRIPTEN_BINDINGS(TransformComponent)
{

    // emscripten::class_<TransformComponent>("TransformComponent")
    //     .property("position", emscripten::optional_override([](TransformComponent &self) -> std::shared_ptr<glm::vec3> {
    //                   return self.position;
    //               }),
    //               emscripten::allow_raw_pointers());
}
