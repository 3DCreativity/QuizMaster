#pragma once
#include "Question.h"
#include "custom_string.h"
#include <fstream>

class MatchingPairQuestion:public Question
{
    private:
        size_t column_separator;
    protected:
        size_t getAnswerCount();
        size_t getCorrectAnswerCount();
    public:
        MatchingPairQuestion(custom_string title, custom_string description, custom_vector<custom_string> choices, custom_string answers,double points,size_t column_separator);

        MatchingPairQuestion(custom_string title, custom_string description, custom_vector<custom_string> choices, custom_string answers, custom_string user_answer,double points,size_t column_separator);

        ~MatchingPairQuestion() override = default;

        double calculatePoints() override;

        void displayQuestion(bool revealAnswers) override;

        custom_string exportAsText() override;
        
        void exportQuestion(std::ofstream& file) override;
        
        static std::unique_ptr<Question> importQuestion(std::ifstream& file);
};