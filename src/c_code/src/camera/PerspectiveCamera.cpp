#include "../../headers/camera/camera.h"

PerspectiveCamera::PerspectiveCamera(int screenWidth,
                                     int screenHeight,
                                     float fov,
                                     float near,
                                     float far,
                                     glm::vec3 pos, glm::vec3 lookAt,
                                     glm::vec3 up)
{
    LOG_CONSTRUCTOR();
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->fov = fov;
    this->near = near;
    this->far = far;
    this->pos = pos;
    this->lookAt = lookAt;
    this->up = up;
    this->projection = glm::perspective(glm::radians(fov), (float)screenWidth / (float)screenHeight, near, far);
    this->view = glm::lookAt(pos, lookAt, up);
};

PerspectiveCamera::~PerspectiveCamera()
{
    LOG_DESTRUCTOR();
}

void PerspectiveCamera::Move(glm::vec3 pos)
{
    this->pos = pos;
    this->view = glm::lookAt(pos, lookAt, up);
}

EMSCRIPTEN_BINDINGS(PerspectiveCamera)
{
    // TODO: move
    emscripten::value_object<glm::vec3>("vec3")
        .field("x", &glm::vec3::x)
        .field("y", &glm::vec3::y)
        .field("z", &glm::vec3::z);

    emscripten::class_<Camera>("Camera")
        .smart_ptr_constructor("Camera", &std::make_shared<Camera>)
        .function("Move", &PerspectiveCamera::Move, emscripten::allow_raw_pointers());

    emscripten::class_<PerspectiveCamera, emscripten::base<Camera>>("PerspectiveCamera")
        .smart_ptr_constructor("PerspectiveCamera", &std::make_shared<PerspectiveCamera>);
}