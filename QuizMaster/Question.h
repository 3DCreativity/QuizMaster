#pragma once
#include "Quiz.h"
#include "Console.h"
#include "custom_hashmap.hpp"
#include "custom_string.h"
#include "FileManager.h"
#include <fstream>
#include <memory>

class Question{
    protected:
        custom_string title;
        custom_string description;
        custom_vector<custom_string> choices;
        custom_string user_answer;
        custom_string answer;
        custom_string answer_syntax;
        double points;
    public:
        Question();

        Question(custom_string title, custom_string description, custom_vector<custom_string> choices, custom_string answer,double points,custom_string answer_syntax);

        Question(custom_string title, custom_string description, custom_vector<custom_string> choices, custom_string answer,custom_string user_answer,double points,custom_string answer_syntax);

        virtual ~Question() = default;

        void setTitle(custom_string title);

        void setDescription(custom_string description);

        void setChoices(custom_vector<custom_string> choices);

        void setUserAnswer(custom_string user_answer);

        void setAnswer(custom_string answer);

        void setPoints(double points);

        void setAnswerSyntax(custom_string syntax);
        
        virtual double calculatePoints() = 0;
        
        void doQuestion();
        
        void givePoints();
        
        virtual void displayQuestion(bool revealAnswers) = 0;
        
        virtual custom_string exportAsText() = 0;
        
        virtual void exportQuestion(std::ofstream& file) = 0;

        static std::unique_ptr<Question> importQuestion(std::ifstream& file);
        
        bool isAnswered();

};