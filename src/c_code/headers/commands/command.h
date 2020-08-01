#pragma once

#include "../../../../include/glm/glm.hpp"
#include "../constants.h"

class BaseCamera;

class Command
{
public:
    virtual void Execute() = 0;
};

class CameraSetViewCommand : public Command
{
private:
    BaseCamera *camera;
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;

public:
    CameraSetViewCommand(BaseCamera *cam, glm::vec3 pos, glm::vec3 front, glm::vec3 up);
    ~CameraSetViewCommand();

    void Execute() override;
};