#include <emscripten.h>
#include <emscripten\bind.h>
#include <memory>

#define DEBUG

#ifdef DEBUG
#define LOG_ERROR(FORMAT, ... ) fprintf(stderr, "%s() in %s, line %i: " FORMAT "\n",  __func__, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_FORMAT(FORMAT, ...) fprintf(stdout, "%s() in %s, line %i: " FORMAT "\n",  __func__, __FILE__, __LINE__, __VA_ARGS__)
#define LOG(MSG) LOG_FORMAT("%s", MSG)
#define LOG_CONSTRUCTOR() LOG("Constructor called.")
#define LOG_DESTRUCTOR() LOG("Destructor called.")
#else
#define LOG_ERROR(FORMAT, ... ) ((void)0)
#define LOG(FORMAT, ...) ((void)0)
#define LOG(MSG) ((void)0)
#define LOG_CONSTRUCTOR() ((void)0)
#define LOG_DESTRUCTOR() ((void)0)
#endif

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600
#define DEFAULT_FOV 60

#define COLOR_SHADER_PATH  "/src/shaders/uniform-color.shader"

