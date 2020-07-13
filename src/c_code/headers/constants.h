#include <emscripten.h>

#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT_FORMAT(FORMAT, ...) \
    printf("%s() in %s, line %i: " FORMAT "\n", \
        __func__, __FILE__, __LINE__, __VA_ARGS__)
    // fprintf(stderr, "%s() in %s, line %i: " FORMAT "\n", \
    //     __func__, __FILE__, __LINE__, __VA_ARGS__)
#define DEBUG_PRINT(MSG) DEBUG_PRINT_FORMAT("%s", MSG)
#else
#define DEBUG_PRINT(FORMAT, ...) ((void)0)
#define DEBUG_PRINT(MSG) ((void)0)
#endif

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600
#define DEFAULT_FOV 60

#define COLOR_SHADER_PATH  "/src/shaders/uniform-color.shader"
