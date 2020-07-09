#include "../../headers/io/filemanger.h"

std::string FileManager::ReadFile(const char *file)
{
    try
    {
        std::ifstream t(file);
        std::string str;

        // more efficient way to read file
        // first set end position
        t.seekg(0, std::ios::end);
        // reserver string up to end positons
        str.reserve(t.tellg());
        // set start of file positions
        t.seekg(0, std::ios::beg);

        // add tp stromg
        str.assign((std::istreambuf_iterator<char>(t)),
                   std::istreambuf_iterator<char>());

        t.close();
        return str;
    }
    catch (std::exception &e)
    {
        printf("%s\n", e.what());
        return "";
    }
}