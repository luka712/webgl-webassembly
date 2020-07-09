#include <string>
#include <fstream>
#include <streambuf>

class FileManager
{
public:
    std::string ReadFile(const char *file);
};