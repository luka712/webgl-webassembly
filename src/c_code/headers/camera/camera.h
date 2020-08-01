#pragma once

#include <string>
#include <deque>
#include "../constants.h"
#include "../commands/command.h"
#include "../../../../include/glm/mat4x4.hpp"
#include "../../../../include/glm/matrix.hpp"
#include "../../../../include/glm/ext.hpp"


class BaseCamera
{
private:
    std::string projectAttrName = "u_projection";
    std::string viewAttrName = "u_view";
  

protected:
    bool active = true;
    const char *type;
    
    std::deque<CameraSetViewCommand *> setViewCommands;
    glm::mat4 projection;
    
    // for playback
    std::reverse_iterator<std::deque<CameraSetViewCommand *>::iterator> it;
    bool playback = false;

public:
    glm::mat4 view;

public:
    BaseCamera();
    ~BaseCamera();
    std::string GetProjectionAttrName() const { return projectAttrName; }
    void SetProjectonAttrName(const std::string v) { projectAttrName = v; }
    std::string GetViewAttrName() const { return viewAttrName; }
    void SetViewAttrName(const std::string v) { viewAttrName = v; }

    glm::mat4 GetProjectionMatrix() { return projection; }
    glm::mat4 &GetViewMatrix() { return view; }

    bool GetActive() const { return active; }
    void SetActive(bool active) { this->active = active; }

    const char* GetType()
     {
        LOG("Calling type");
        return type;
    }

    virtual void Update() {}
    virtual void Move(glm::vec3 pos) {}
    virtual void LookAt(glm::vec3 lookAt) {}
    virtual void Playback() {}
};

class PerspectiveCamera : public BaseCamera
{
private:
    int screenWidth;
    int screenHeight;
    float fov;
    float nearPlane;
    float farPlane;

protected:
    glm::vec3 pos;
    glm::vec3 lookAt;
    glm::vec3 worldUp;

public:
    PerspectiveCamera(int screenWidth = DEFAULT_WIDTH,
                      int screenHeight = DEFAULT_HEIGHT,
                      float fov = DEFAULT_FOV,
                      float nearPlane = 0.1f,
                      float farPlane = 100.0f,
                      glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 lookAt = glm::vec3(0.0f, 0.0f, -1.0f),
                      glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f));
    ~PerspectiveCamera();

    void Move(glm::vec3 pos) override;
    void LookAt(glm::vec3 lookAt) override;
};

enum FreeCameraActions
{
    MoveLeft = 0,
    MoveRight,
    MoveForward,
    MoveBackwards
};

class FreeCamera : public PerspectiveCamera
{
private:
    std::map<SDL_Keycode, FreeCameraActions> mappingToKeys;
    std::map<FreeCameraActions, bool> mappingToActionToExecute;
    float moveSpeed;
    float turnSpeed;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    float yaw;
    float pitch;
    float previousDx;
    float previousDy;
    float dx;
    float dy;

    void HandleEvents();
    void UpdateKeys();
    void UpdateMouse();

public:
    FreeCamera(int screenWidth = DEFAULT_WIDTH,
               int screenHeight = DEFAULT_HEIGHT,
               float fov = DEFAULT_FOV,
               float nearPlane = 0.1f,
               float farPlane = 100.0f,
               glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f),
               glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f),
               float yaw = -90.0f,
               float pitch = 0.0f,
               float moveSpeed = 0.25f,
               float turnSpeed = 0.15f);
    ~FreeCamera();

    void Update() override;
    void Move(glm::vec3 pos) override;
    void LookAt(glm::vec3 lookAt) override;
    void Playback() override;
};