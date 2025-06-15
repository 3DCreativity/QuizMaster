#pragma once
#include "Question.h"
#include "custom_string.h"
#include <fstream>


class MultipleChoiceQuestion:public Question{  
    private:
        size_t getAnswerCount();
        size_t getCorrectAnswerCount();
    public:
        MultipleChoiceQuestion(custom_string title, custom_string description, custom_vector<custom_string> choices, custom_string answer,double points);
        MultipleChoiceQuestion(custom_string title, custom_string description, custom_vector<custom_string> choices, custom_string answer, custom_string user_answer,double points);
        ~MultipleChoiceQuestion() override = default;
        double calculatePoints() override;
        void displayQuestion(bool revealAnswers) override;
        custom_string exportAsText() override;
        void exportQuestion(std::ofstream& file) override;
        static std::unique_ptr<Question> importQuestion(std::ifstream& file);
};