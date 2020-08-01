#include "../../headers/commands/command.h"
#include "../../headers/camera/camera.h"

CameraSetViewCommand::CameraSetViewCommand(BaseCamera *camera, glm::vec3 pos, glm::vec3 front, glm::vec3 up)
    : camera(camera), pos(pos), front(front), up(up)
{
}

CameraSetViewCommand::~CameraSetViewCommand()
{
    LOG_DESTRUCTOR();
}

void CameraSetViewCommand::Execute()
{
    camera->view = glm::lookAt(pos, pos + front, up);
}