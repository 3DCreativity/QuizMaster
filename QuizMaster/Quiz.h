#pragma once
#include "Question.h"
#include "custom_vector.hpp"
#include "custom_string.h"
#include "FileManager.h"
#include <fstream>
#include <memory>

class Question;

class Quiz
{
    private:
        static Quiz* instance;
        custom_string name;
        size_t id;
        custom_string author_name;
        custom_string author_username;
        custom_vector<std::unique_ptr<Question>> questions;
        double points;
        void shuffleQuestions();
        void generateID();
    public:
        bool test_mode;
        static void loadQuiz();
        static Quiz& getInstance();
        Quiz(custom_string name,size_t id, custom_string author_name, custom_string author_username, custom_vector<std::unique_ptr<Question>> questions, double points = 0);
        Quiz(custom_string name, custom_string author_name, custom_string author_username, double points = 0);
        ~Quiz();
        void addQuestion();
        void doQuiz(bool shuffle = false);
        void addPoints(double points);
        void exportQuiz(std::ofstream& file);
        void importQuiz(std::ifstream& file);
        void saveAsText();
};