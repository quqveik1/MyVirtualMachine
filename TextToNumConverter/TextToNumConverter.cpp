#define _CRT_SECURE_NO_WARNINGS

#include "Converter.cpp"

int main(int argc, char** argv)
{

    std::string path = "../AsmCode/Sinus.asm";
    bool needToCreateFileListing = false;

    if(argc > 1)
    {
        path = std::string(argv[1], argv[1] + std::strlen(argv[1]));
    }
    if(argc > 2)
    {
        std::string option_str(argv[2]);
        needToCreateFileListing = (option_str == "true" || option_str == "1");
    }

    compile(path, needToCreateFileListing);
}