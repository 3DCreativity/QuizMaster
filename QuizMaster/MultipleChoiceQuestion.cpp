#include "MultipleChoiceQuestion.h"
#include "Question.h"
#include "custom_hashmap.hpp"
#include "custom_string.h"
#include "custom_vector.hpp"
#include "Console.h"
#include <fstream>

size_t MultipleChoiceQuestion::getAnswerCount()
{
    custom_vector<custom_string> pairs = user_answer.split(' ');
    custom_vector<custom_string> correct_pairs = answer.split(' ');
    size_t counter = 0;
    for(size_t i=0;i<correct_pairs.getSize();i++)
    {
        if(pairs.findFirstMatch(correct_pairs[i]) != -1)
        {
            counter++;
        }
    }
    return counter;
}

size_t MultipleChoiceQuestion::getCorrectAnswerCount()
{
    custom_vector<custom_string> pairs = answer.split(' ');
    return pairs.getSize();
}

MultipleChoiceQuestion::MultipleChoiceQuestion(custom_string title, custom_string description, custom_vector<custom_string> choices, custom_string answer,double points):
Question(title,description,choices,answer,points,"Answer syntax: <index> <index> <index>...\nNote: The key SPACE is a separator. Be careful where you use it\n\nEnter your answer: ")
{}

MultipleChoiceQuestion::MultipleChoiceQuestion(custom_string title, custom_string description, custom_vector<custom_string> choices, custom_string answer,custom_string user_answer,double points):
Question(title,description,choices,answer,user_answer,points,"Answer syntax: <index> <index> <index>...\nNote: The key SPACE is a separator. Be careful where you use it\n\nEnter your answer: ")
{}

double MultipleChoiceQuestion::calculatePoints()
{
    size_t correct_answer_count = getCorrectAnswerCount();
    size_t answer_count = getAnswerCount();
    if(answer_count < correct_answer_count/2)
    {
        return 0;
    }
    else if (answer_count >= correct_answer_count/2 && answer_count != correct_answer_count)
    {
        return points/2;
    }
    else
    {
        return points;
    }
}


void MultipleChoiceQuestion::displayQuestion(bool revealAnswers)
{
    Console::displayMessage(exportAsText());

    if(revealAnswers)
    {
        Console::displayMessage("Answers:\n");
        custom_vector<custom_string> answers = answer.split(' ');
        for(size_t i=0;i<answers.getSize();i++)
        {
            Console::displayMessage(answers[i]);
        }
    }

    Console::displayMessage("\n");
}

custom_string MultipleChoiceQuestion::exportAsText()
{
    custom_string result;
    result+=title + "\n";
    result+=description + "\n";
    for(size_t i=0;i<choices.getSize();i++)
    {
        result+= custom_string((int)i) + " " + choices[i] + "\n";
    }
    

    result+="\n\n";

    return result;
}

void MultipleChoiceQuestion::exportQuestion(std::ofstream& file)
{
    int type = 3;
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

    size_t choices_count = choices.getSize();
    file.write(reinterpret_cast<const char*>(&choices_count),sizeof(choices_count));

    size_t choice_len;
    for(size_t i=0;i<choices_count;i++)
    {
        choice_len = choices[i].len();
        file.write(reinterpret_cast<const char*>(&choice_len), sizeof(choice_len));
        file.write(choices[i].c_str(),choice_len);
    }
}  

std::unique_ptr<Question> MultipleChoiceQuestion::importQuestion(std::ifstream& file)
{
    custom_string title;
    custom_string description;
    custom_vector<custom_string> choices;
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

    size_t choices_count;
    file.read(reinterpret_cast<char*>(&choices_count),sizeof(choices_count));


    for(size_t i=0;i<choices_count;i++)
    {
        file.read(reinterpret_cast<char*>(&len),sizeof(len));

        str = new char[len + 1];
        file.read(str,len);
        str[len] = '\0';
        choices.add(str);
        delete[] str;
    }

    return std::make_unique<MultipleChoiceQuestion>(title,description,choices,answer,user_answer,points);
}
