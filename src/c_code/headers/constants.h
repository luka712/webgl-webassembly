#include <emscripten.h>

#define DEBUG

#ifdef DEBUG
#define DEBUG_LOG(x) printf("%s\n", x)
#else 
#define DEBUG(x) do {} while (0)
#endif

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600
#define DEFAULT_FOV 60

#define COLOR_SHADER_PATH  "/src/shaders/uniform-color.shader"
