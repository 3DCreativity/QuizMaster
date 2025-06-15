#include "Question.h"
#include "SingleChoiceQuestion.h"
#include "MultipleChoiceQuestion.h"
#include "ShortAnswerQuestion.h"
#include "MatchingPairQuestion.h"
#include "TrueOrFalseQuestion.h"
#include "custom_string.h"
#include "custom_vector.hpp"
#include "Console.h"
#include <stdexcept>

Question::Question():points(0) {}

Question::Question(custom_string title, custom_string description, custom_vector<custom_string> choices, custom_string answer,double points,custom_string answer_syntax):
        title(title),description(description),choices(choices),answer(answer),points(points),answer_syntax(answer_syntax) {}


Question::Question(custom_string title, custom_string description, custom_vector<custom_string> choices, custom_string answer,custom_string user_answer,double points,custom_string answer_syntax):
        title(title),description(description),choices(choices),answer(answer),user_answer(user_answer),points(points),answer_syntax(answer_syntax) {}

void Question::setTitle(custom_string title)
{
    this->title = title;
}

void Question::setDescription(custom_string description)
{
    this->description = description;
}

void Question::setChoices(custom_vector<custom_string> choices)
{
    this->choices = choices;
}

void Question::setUserAnswer(custom_string user_answer)
{
    this->user_answer = user_answer;
}

void Question::setAnswer(custom_string answer)
{
    this->answer = answer;
}

void Question::setPoints(double points)
{
    if(points>=0){
        this->points = points;
    }
}

void Question::setAnswerSyntax(custom_string syntax)
{
    this->answer_syntax = syntax;
}

void Question::doQuestion()
{
    try{
        displayQuestion(false);
        while(true)
        {
            user_answer = Console::prompt_ignore_buffer(answer_syntax);
            if(Console::prompt_ignore_buffer("Take a good look at your answer. Do you wish to continue(you won't be able to redact the question afterwards.) (y/n): ") == "y")
            {
                break;
            }
        }
        if(Quiz::getInstance().test_mode == true)
        {
            Console::displayMessage("\n\n\n");
            displayQuestion(true);
            Console::prompt_ignore_buffer("Press ENTER to continue...");
        }
    }
    catch(std::invalid_argument e)
    {
        Console::displayError(e.what());
    }
    givePoints();

}

void Question::givePoints()
{
    try{
        if(Quiz::getInstance().test_mode == false){
            Quiz::getInstance().addPoints(calculatePoints());
        }
    }
    catch(std::invalid_argument e)
    {
        Console::displayError(e.what());
    }
}

bool Question::isAnswered()
{
    return user_answer != "";
}

std::unique_ptr<Question> Question::importQuestion(std::ifstream& file)
{
    int type;
    file.read(reinterpret_cast<char*>(&type),sizeof(type));

    switch(type)
    {
        case 2:
            return SingleChoiceQuestion::importQuestion(file);
            break;
        case 3:
            return MultipleChoiceQuestion::importQuestion(file);
            break;
        case 4:
            return ShortAnswerQuestion::importQuestion(file);
            break;
        case 5:
            return MatchingPairQuestion::importQuestion(file);
            break;
        default:
            Console::displayError("Unable to extract Type when reading the Quiz");
            break;
    }
    return std::make_unique<TrueOrFalseQuestion>("Unknown","Undefined",false,0);
}
