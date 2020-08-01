#include "../../headers/camera/camera.h"

PerspectiveCamera::PerspectiveCamera(int screenWidth,
                                     int screenHeight,
                                     float fov,
                                     float nearPlane,
                                     float farPlane,
                                     glm::vec3 pos,
                                     glm::vec3 lookAt,
                                     glm::vec3 worldUp)
{
    LOG_CONSTRUCTOR();

    this->type = typeid(this).name();

    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->fov = fov;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;
    this->pos = pos;
    this->lookAt = lookAt;
    this->worldUp = worldUp;
    this->projection = glm::perspective(glm::radians(fov), (float)screenWidth / (float)screenHeight, nearPlane, farPlane);
    this->view = glm::lookAt(pos, lookAt, worldUp);
};

PerspectiveCamera::~PerspectiveCamera()
{
    LOG_DESTRUCTOR();
}

void PerspectiveCamera::Move(glm::vec3 pos)
{
    this->pos = pos;
    this->view = glm::lookAt(pos, lookAt, worldUp);
}

void PerspectiveCamera::LookAt(glm::vec3 pos)
{
    this->lookAt = lookAt;
    this->view = glm::lookAt(pos, lookAt, worldUp);
}

EMSCRIPTEN_BINDINGS(PerspectiveCamera)
{
    emscripten::class_<PerspectiveCamera, emscripten::base<BaseCamera>>("PerspectiveCamera")
        .smart_ptr_constructor("PerspectiveCamera", &std::make_shared<PerspectiveCamera>);
}