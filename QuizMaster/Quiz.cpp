#include "Quiz.h"
#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include "Question.h"
#include "TrueOrFalseQuestion.h"
#include "SingleChoiceQuestion.h"
#include "MultipleChoiceQuestion.h"
#include "MatchingPairQuestion.h"
#include "ShortAnswerQuestion.h"
#include "NormalExit.hpp"
#include "User.h"
#include <memory>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <fstream>

Quiz* Quiz::instance = nullptr;


void Quiz::shuffleQuestions()
{
    custom_vector<size_t> past_indexes;
    custom_vector<std::unique_ptr<Question>> shuffled;
    std::srand(std::time(0));

    int random_number;
    size_t questions_size = questions.getSize();

    while(past_indexes.getSize() != questions_size)
    {
        random_number = std::rand() % questions_size;
        if(past_indexes.findFirstMatch(random_number) == -1)
        {
            past_indexes.add(random_number);
            shuffled.add(std::move(questions[random_number]));
        }
    }

    questions = std::move(shuffled);

}

void Quiz::generateID()
{
    std::srand(std::time(0));
    do
    {
        id = std::rand() % (1000 + 1);
    } while (false /*FileManager::checkFileExistance*/);
    
}

void Quiz::loadQuiz()
{
    //FileManager Schenanigans
    instance = new Quiz("Test","System","system");
}


Quiz& Quiz::getInstance(){
    if(instance == nullptr)
    {
        throw std::invalid_argument("No active Quiz is available");
    }
    return *Quiz::instance;
}

Quiz::Quiz(custom_string name,size_t id, custom_string author_name, custom_string author_username, custom_vector<std::unique_ptr<Question>> questions, double points):
name(name),id(id),author_name(author_name),author_username(author_username),questions(questions),points(points) {
    test_mode = false;
}

Quiz::Quiz(custom_string name, custom_string author_name, custom_string author_username, double points):name(name),author_name(author_name),author_username(author_username),points(points)
{
    generateID();
    test_mode = false;
}

Quiz::~Quiz()
{
    Quiz::instance = nullptr;
}

void Quiz::addQuestion()
{
    custom_string title;
    custom_string descr;
    custom_vector<custom_string> choices;
    custom_string correctAnswer;
    double points;
    int choice_count;
    switch(Console::prompt_ignore_buffer("Enter type of Question you want to add\nTrue/False -> 1\nSingle Choice -> 2\nMulti Choice -> 3\nShort Answer -> 4\nMatching Pairs -> 5\n\n: ").toInt())
    {
        case 1:
        {
            title = Console::prompt_ignore_buffer("Enter question title(optional): ");
            descr = Console::prompt_ignore_buffer("Enter question description: ");
            correctAnswer = Console::prompt_ignore_buffer("Enter the correct answer to the question (True/False = default): ");
            points = Console::prompt_ignore_buffer("Enter how many points should the player get for a correct answer (whole number): ").toInt();
            questions.add(std::make_unique<TrueOrFalseQuestion>(title,descr,correctAnswer.toBool(),points));
            break;
        }
        case 2:
        {
            title = Console::prompt_ignore_buffer("Enter question title(optional): ");
            descr = Console::prompt_ignore_buffer("Enter question description: ");
            for(int i=1;i<=4;i++)
            {
                choices.add(Console::prompt_ignore_buffer(custom_string() + "Enter choice " + i + ": "));
            }
            correctAnswer = Console::prompt_ignore_buffer("Enter the correct answer to the question: ");
            points = Console::prompt_ignore_buffer("Enter how many points should the player get for a correct answer (whole number): ").toInt();
            questions.add(std::make_unique<SingleChoiceQuestion>(title,descr,choices,correctAnswer,points));
            break;
        }
        case 3:
        {
            title = Console::prompt_ignore_buffer("Enter question title(optional): ");
            descr = Console::prompt_ignore_buffer("Enter question description: ");
            while(true)
            {
                choice_count = Console::prompt_ignore_buffer("Enter how many choices this question has (>=4): ").toInt();
                if(choice_count >= 4)
                {
                    break;
                }
                Console::displayMessage("The question count must be at least 4 choices");
            }
            for(int i=1;i<=choice_count;i++)
            {
                choices.add(Console::prompt_ignore_buffer(custom_string() + "Enter choice " + i + ": "));
            }
            correctAnswer = Console::prompt_ignore_buffer("Enter the correct answer to the question: ");
            points = Console::prompt_ignore_buffer("Enter how many points should the player get for a correct answer (whole number): ").toInt();
            questions.add(std::make_unique<MultipleChoiceQuestion>(title,descr,choices,correctAnswer,points));
            break;
        }
        case 4:
        {
            title = Console::prompt_ignore_buffer("Enter question title(optional): ");
            descr = Console::prompt_ignore_buffer("Enter question description: ");
            correctAnswer = Console::prompt_ignore_buffer("Enter the correct answer to the question: ");
            points = Console::prompt_ignore_buffer("Enter how many points should the player get for a correct answer (whole number): ").toInt();
            questions.add(std::make_unique<ShortAnswerQuestion>(title,descr,correctAnswer,points));
            break;
        }
        case 5:
        {
            title = Console::prompt_ignore_buffer("Enter question title(optional): ");
            descr = Console::prompt_ignore_buffer("Enter question description: ");
            while(true)
            {
                choice_count = Console::prompt_ignore_buffer("Enter how many choices this question has (>=2): ").toInt();
                if(choice_count >= 2)
                {
                    break;
                }
                Console::displayMessage("The question count must be at least 2 choices");
            }
            int column_separator;
            while(true)
            {
                column_separator = Console::prompt_ignore_buffer("Enter how many choices the first column has: ").toInt();
                if(column_separator > 0 && column_separator < choice_count)
                {
                    break;
                }
                Console::displayMessage("The question column must have at least 1 choice and be in the choice count");
            }
            Console::displayMessage("First column:\n");
            int i = 0;
            for(;i<column_separator;i++)
            {
                choices.add(Console::prompt_ignore_buffer(custom_string() + "Enter choice " + i + ": "));
            }
            Console::displayMessage("\nSecond Column: \n");
            for(;i<choice_count;i++)
            {
                choices.add(Console::prompt_ignore_buffer(custom_string() + "Enter choice " + i + ": "));
            }
            correctAnswer = Console::prompt_ignore_buffer("Enter the correct answer to the question: ");
            points = Console::prompt_ignore_buffer("Enter how many points should the player get for a correct answer (whole number): ").toInt();
            questions.add(std::make_unique<MatchingPairQuestion>(title,descr,choices,correctAnswer,points,column_separator));
            break;
        }
        default:
        {
            Console::displayMessage("Invalid type entered\nNo question has been added");
            break;
        }
    }
}

void Quiz::doQuiz(bool shuffle)
{
    if (shuffle)
    {
        shuffleQuestions();
    }
    for(size_t i=0;i<questions.getSize();i++)
    {
        if(questions[i]->isAnswered())
        {
            questions[i]->givePoints();
            continue;
        }
        switch(Console::prompt_ignore_buffer("What do you want to do now?\n1 -> Do the next question\n2 -> Quit program\n\n:").toInt())
        {
            case 1:
                questions[i]->doQuestion();
                break;
            case 2:
                // saveProgress();
                throw NormalExit("Quitting mid-quiz.\nSaving progress...\nQuitting program...");
                break;
            default:
                Console::displayMessage("Invalid operation was passed\nTry again.");
                i--;
                break;
        }
    }

    User::getInstance().addPoints(points);

}

void Quiz::addPoints(double points)
{
    this->points += points;
}

void Quiz::exportQuiz(std::ofstream& file)
{
    file.write(reinterpret_cast<const char*>(&id),sizeof(id));

    size_t author_username_len = author_username.len();
    file.write(reinterpret_cast<const char*>(&author_username_len), sizeof(author_username_len));
    file.write(author_username.c_str(),author_username_len);

    size_t name_len = name.len();
    file.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
    file.write(name.c_str(),name_len);

    size_t author_name_len = author_name.len();
    file.write(reinterpret_cast<const char*>(&author_name_len), sizeof(author_name_len));
    file.write(author_name.c_str(),author_name_len);

    file.write(reinterpret_cast<const char*>(&points),sizeof(points));

    size_t question_count = questions.getSize();
    file.write(reinterpret_cast<const char*>(&question_count), sizeof(question_count));

    for(size_t i=0;i<question_count;i++)
    {
        questions[i]->exportQuestion(file);
    }


}

void Quiz::importQuiz(std::ifstream& file)
{
    size_t len;
    char* str;

    file.read(reinterpret_cast<char*>(&id),sizeof(id));

    file.read(reinterpret_cast<char*>(&len),sizeof(len));

    str = new char[len + 1];
    file.read(str,len);
    str[len] = '\0';
    author_username = str;
    delete[] str;

    file.read(reinterpret_cast<char*>(&len),sizeof(len));

    str = new char[len + 1];
    file.read(str,len);
    str[len] = '\0';
    name = str;
    delete[] str;

    file.read(reinterpret_cast<char*>(&len),sizeof(len));

    str = new char[len + 1];
    file.read(str,len);
    str[len] = '\0';
    author_name = str;
    delete[] str;

    file.read(reinterpret_cast<char*>(&points),sizeof(points));

    size_t question_count;
    file.read(reinterpret_cast<char*>(&question_count),sizeof(question_count));

    for(size_t i=0;i<question_count;i++)
    {
        questions.add(std::move(Question::importQuestion(file)));
    }
}

void Quiz::saveAsText()
{
    custom_string info = name + " - " + (int)questions.getSize() + " Questions\nBy " + author_name + " @" + author_username + "\n";
    for(size_t i=0;i<questions.getSize();i++)
    {
        info += custom_string() + (int)i + ") " + questions[i]->exportAsText() + "\n\n";
    }
    //FileManager.writeTextFile(Console::prompt_ignore_buffer("Enter full address of where you wish to save the file(Be careful - no failsafe.): "),info);
}
