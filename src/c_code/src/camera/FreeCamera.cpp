#include "../../headers/camera/camera.h"

FreeCamera::FreeCamera(int screenWidth,
                       int screenHeight,
                       float fov,
                       float nearPlane,
                       float farPlane,
                       glm::vec3 pos,
                       glm::vec3 worldUp,
                       float yaw,
                       float pitch,
                       float moveSpeed,
                       float turnSpeed) : PerspectiveCamera(screenWidth, screenHeight, fov, nearPlane, farPlane, pos, glm::vec3(0.0f, 0.0f, -1.0f), worldUp)
{
    LOG_CONSTRUCTOR();

    this->type = typeid(this).name();

    this->projection = glm::perspective(glm::radians(fov), (float)screenWidth / (float)screenHeight, nearPlane, farPlane);
    this->front = glm::vec3(0.0f, 0.0f, -1.0f);
    this->view = glm::lookAt(pos, front, worldUp);

    mappingToActionToExecute.emplace(FreeCameraActions::MoveLeft, false);
    mappingToActionToExecute.emplace(FreeCameraActions::MoveRight, false);
    mappingToActionToExecute.emplace(FreeCameraActions::MoveForward, false);
    mappingToActionToExecute.emplace(FreeCameraActions::MoveBackwards, false);

    mappingToKeys.emplace(SDLK_a, FreeCameraActions::MoveLeft);
    mappingToKeys.emplace(SDLK_d, FreeCameraActions::MoveRight);
    mappingToKeys.emplace(SDLK_w, FreeCameraActions::MoveForward);
    mappingToKeys.emplace(SDLK_s, FreeCameraActions::MoveBackwards);

    this->moveSpeed = moveSpeed;
    this->turnSpeed = turnSpeed;
    this->yaw = yaw;
    this->pitch = pitch;

    dx = 0.0f;
    dy = 0.0f;

    previousDx = 0.0f;
    previousDy = 0.0f;

    SDL_SetRelativeMouseMode(SDL_TRUE);
};

FreeCamera::~FreeCamera()
{
    LOG_DESTRUCTOR();
}

void FreeCamera::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            if (mappingToKeys.count(event.key.keysym.sym))
            {
                FreeCameraActions action = mappingToKeys.find(event.key.keysym.sym)->second;
                mappingToActionToExecute.find(action)->second = true;
            }
            break;

        case SDL_KEYUP:
            if (mappingToKeys.count(event.key.keysym.sym))
            {
                FreeCameraActions action = mappingToKeys.find(event.key.keysym.sym)->second;
                mappingToActionToExecute.find(action)->second = false;
            }
            break;
        case SDL_MOUSEMOTION:
            dx = event.motion.xrel;
            dy = -event.motion.yrel;

            break;
        }
    }
}

void FreeCamera::UpdateKeys()
{
    for (auto &[k, v] : mappingToActionToExecute)
    {
        if (v)
        {
            switch (k)
            {
            case FreeCameraActions::MoveRight:
                pos += right * moveSpeed;
                break;
            case FreeCameraActions::MoveLeft:
                pos -= right * moveSpeed;
                break;
            case FreeCameraActions::MoveForward:
                pos += front * moveSpeed;
                break;
            case FreeCameraActions::MoveBackwards:
                pos -= front * moveSpeed;
                break;
            }
        }
    }
}

void FreeCamera::UpdateMouse()
{
    dx *= turnSpeed;
    dy *= turnSpeed;

    yaw += dx;
    pitch += dy;

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }

    if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    previousDx = dx;
    previousDy = dy;
}

void FreeCamera::Update()
{
    if (!active)
        return;

    HandleEvents();
    UpdateMouse();

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));

    UpdateKeys();

    //this->view = glm::lookAt(pos, pos + front, up);

    // do not enter new command if on playback
    if (!playback)
    {
        auto command = new CameraSetViewCommand(this, pos, front, up);
        setViewCommands.push_back(command);
        if (setViewCommands.size() > 60 * 60)
        {
            setViewCommands.pop_front();
        }
        command->Execute();
    }
    else 
    {
        if(it != setViewCommands.rend())
        {
            (*it)->Execute();
            ++it;
        }
    }
}

void FreeCamera::Move(glm::vec3 pos)
{
    this->pos = pos;
    this->view = glm::lookAt(pos, lookAt, worldUp);
}

void FreeCamera::LookAt(glm::vec3 pos)
{
    this->lookAt = lookAt;
    this->pitch = 0;
    this->yaw = 0;
    this->dx = 0;
    this->dy = 0;
    this->view = glm::lookAt(pos, lookAt, worldUp);
}

void FreeCamera::Playback()
{
    LOG_FORMAT("size %d", setViewCommands.size());

    // start playback
    playback = true;
    // rbegin is end of collection, rend is start. So this is reverse iterrator end -> begin
    it = setViewCommands.rbegin();
}

EMSCRIPTEN_BINDINGS(FreeCamera)
{
    emscripten::class_<FreeCamera, emscripten::base<PerspectiveCamera>>("FreeCamera")
        .smart_ptr_constructor("FreeCamera", &std::make_shared<FreeCamera>);
}