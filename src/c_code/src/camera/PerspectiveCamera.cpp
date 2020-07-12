#include "../../headers/camera/camera.h"

PerspectiveCamera::PerspectiveCamera(int screenWidth,
                                     int screenHeight,
                                     float fov,
                                     float near,
                                     float far,
                                     glm::vec3 pos, glm::vec3 lookAt,
                                     glm::vec3 up)
{
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

void PerspectiveCamera::Move(glm::vec3 pos)
{
    this->pos = pos;
    this->view = glm::lookAt(pos, lookAt, up);
}