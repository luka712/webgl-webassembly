#include <emscripten.h>
#include <emscripten/fetch.h>
#include <string.h>
#include <stdio.h>

class FileLoader 
{
    public:
        void LoadFile(const char *filename);
};