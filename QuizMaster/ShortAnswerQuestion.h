#pragma once
#include "Question.h"
#include "custom_string.h"
#include "custom_vector.hpp"
#include <fstream>

class ShortAnswerQuestion:public Question
{
    public:
        ShortAnswerQuestion(custom_string title, custom_string description, custom_string answer, double points);

        ShortAnswerQuestion(custom_string title, custom_string description, custom_string answer,custom_string user_answer, double points);

        ~ShortAnswerQuestion() override = default;

        double calculatePoints() override;

        void displayQuestion(bool revealAnswers) override;

        custom_string exportAsText() override;
        
        void exportQuestion(std::ofstream& file) override;

        static std::unique_ptr<Question> importQuestion(std::ifstream& file);

};