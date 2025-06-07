#include <iostream>
#include "Console.h"
#include "NormalExit.hpp"

int main()
{
    while(true)
    {
        try
        {
            Console::update();
        }
        catch(const NormalExit& e)
        {
            std::cout << e.what() << std::endl;
            break;
        }
        catch(...)
        {
            std::cout << "Unknown error\n" << std::endl;
            break;
        }
    }
    return 0;
}