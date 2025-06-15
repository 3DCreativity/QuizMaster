#include "ShortAnswerQuestion.h"
#include "custom_vector.hpp"
#include "Console.h"
#include "custom_string.h"
#include <fstream>

ShortAnswerQuestion::ShortAnswerQuestion(custom_string title, custom_string description, custom_string answer, double points):Question()
{
    setTitle(title);
    setDescription(description);
    setPoints(points);
    setAnswer(answer);
    setAnswerSyntax("Answer syntax: <answer>\nNote: This type of question does not support multi-line answers.\nThis type of question is case-sensitive\n\nEnter your answer: ");
}

ShortAnswerQuestion::ShortAnswerQuestion(custom_string title, custom_string description, custom_string answer, custom_string user_answer, double points):Question()
{
    setTitle(title);
    setDescription(description);
    setPoints(points);
    setAnswer(answer);
    setUserAnswer(user_answer);
    setAnswerSyntax("Answer syntax: <answer>\nNote: This type of question does not support multi-line answers.\nThis type of question is case-sensitive\n\nEnter your answer: ");
}

double ShortAnswerQuestion::calculatePoints()
{
    if(user_answer == answer)
    {
        return points;
    }
    return 0;
}

void ShortAnswerQuestion::displayQuestion(bool revealAnswers) 
{
    Console::displayMessage(exportAsText());

    if(revealAnswers)
    {
        Console::displayMessage("Answer:\n" + answer);
    }

    Console::displayMessage("\n");
}  

custom_string ShortAnswerQuestion::exportAsText()
{
    custom_string result;
    result+=title + "\n";
    result+=description + "\n";
    result+="\n";

    return result;
}

void ShortAnswerQuestion::exportQuestion(std::ofstream& file)
{
    int type = 4;
    file.write(reinterpret_cast<const char*>(&type),sizeof(type));

    size_t title_len = title.len();
    file.write(reinterpret_cast<const char*>(&title_len), sizeof(title_len));
    file.write(title.c_str(),title_len);

    size_t desc_len = description.len();
    file.write(reinterpret_cast<const char*>(&desc_len), sizeof(desc_len));
    file.write(description.c_str(),desc_len);

    size_t asnwer_len = answer.len();
    file.write(reinterpret_cast<const char*>(&asnwer_len), sizeof(asnwer_len));
    file.write(answer.c_str(),asnwer_len);

    size_t user_answer_len = user_answer.len();
    file.write(reinterpret_cast<const char*>(&user_answer_len), sizeof(user_answer_len));
    file.write(user_answer.c_str(),user_answer_len);   
    
    file.write(reinterpret_cast<const char*>(&points),sizeof(points));

}

std::unique_ptr<Question> ShortAnswerQuestion::importQuestion(std::ifstream& file)
{
    custom_string title;
    custom_string description;
    custom_string user_answer;
    custom_string answer;
    double points;

    size_t len;
    char* str;
    file.read(reinterpret_cast<char*>(&len),sizeof(len));

    str = new char[len + 1];
    file.read(str,len);
    str[len] = '\0';
    title = str;
    delete[] str;

    file.read(reinterpret_cast<char*>(&len),sizeof(len));

    str = new char[len + 1];
    file.read(str,len);
    str[len] = '\0';
    description = str;
    delete[] str;

    file.read(reinterpret_cast<char*>(&len),sizeof(len));

    str = new char[len + 1];
    file.read(str,len);
    str[len] = '\0';
    answer = str;
    delete[] str;

    file.read(reinterpret_cast<char*>(&len),sizeof(len));

    str = new char[len + 1];
    file.read(str,len);
    str[len] = '\0';
    user_answer = str;
    delete[] str;

    file.read(reinterpret_cast<char*>(&points),sizeof(points));

    return std::make_unique<ShortAnswerQuestion>(title,description,answer,user_answer,points);
}
