#include "../../headers/camera/camera.h"

BaseCamera::BaseCamera()
{
    LOG_CONSTRUCTOR();
    this->type = typeid(this).name();
}

BaseCamera::~BaseCamera()
{
    delete type;
    for (auto command : setViewCommands)
    {
        delete command;
    }
    LOG_DESTRUCTOR();
}

EMSCRIPTEN_BINDINGS(BaseCamera)
{
    emscripten::class_<BaseCamera>("BaseCamera")
        .smart_ptr_constructor("BaseCamera", &std::make_shared<BaseCamera>)
        .function("Move", &PerspectiveCamera::Move, emscripten::allow_raw_pointers())
        .function("LookAt", &PerspectiveCamera::LookAt, emscripten::allow_raw_pointers())
        .function("Playback", &BaseCamera::Playback)
        .function("GetType", &BaseCamera::GetType, emscripten::allow_raw_pointers())
        .property("active", &BaseCamera::GetActive, &BaseCamera::SetActive);
}
