#include "ReadCommands.cpp"

int main(int argc, char** argv)
{

    /*
    double res = sinus(M_PI, 8);
    std::cout << "PI: " << res << "\n";
    res = sinus(M_PI/2, 8);
    std::cout << "PI/2: " << res << "\n";
    */

    return (int)readByteCode("AsmCode/TrueSin.bin");
}
