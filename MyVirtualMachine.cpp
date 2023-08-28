#include "ReadCommands.cpp"

int main(int argc, char** argv)
{

    std::string path = "../BadApple/Code/asmCode1.bin";
    int sizeX = 268;
    int sizeY = 201;

    if (argc >= 2)
    {
        path = std::string(argv[1], argv[1] + std::strlen(argv[1]));
    }
    if (argc == 4)
    {
        try 
        {
            sizeX = std::stoi(argv[2]);
            sizeY = std::stoi(argv[3]);
        }
        catch (const std::exception& e) 
        {
            std::cout << "Error during size conversion: " << e.what() << '\n';
            return 1;
        }
    }

    return (int)readByteCode(path, sizeX, sizeY);
}
