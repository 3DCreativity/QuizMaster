#pragma once
#include "Question.h"
#include "custom_hashmap.hpp"
#include "custom_string.h"
#include "custom_vector.hpp"
#include <fstream>

class SingleChoiceQuestion:public Question
{
    public:
        SingleChoiceQuestion(custom_string title, custom_string description, bool answer, double points);
        SingleChoiceQuestion(custom_string title, custom_string description, custom_vector<custom_string> choices, custom_string answer,double points);
        SingleChoiceQuestion(custom_string title, custom_string description, custom_vector<custom_string> choices, custom_string answer,custom_string user_answers,double points);
        ~SingleChoiceQuestion() override = default;
        double calculatePoints() override;
        void displayQuestion(bool revealAnswers) override;
        custom_string exportAsText() override;
        void exportQuestion(std::ofstream& file) override;
        static std::unique_ptr<Question> importQuestion(std::ifstream& file);
};