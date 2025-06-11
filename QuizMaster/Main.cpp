#include <iostream>
#include "Console.h"
#include "NormalExit.hpp"

int main()
{
    Console::displayMessage(custom_string() +
                            "Hello and Welcome to QuizMaster\n" +
                            "The platform for creating and doing quizzes\n" +
                            "acting as a social media for quizzes.\n\n" + 
                            "For any questions, please consult an Administrator or the Manual.\n");
    custom_string test = -1;
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