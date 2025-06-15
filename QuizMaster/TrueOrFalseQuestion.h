#pragma once
#include "Question.h"
#include "SingleChoiceQuestion.h"
#include "custom_hashmap.hpp"
#include "custom_string.h"
#include "custom_vector.hpp"

//This class is more or less useless, due to the SingleChoiceQuestion class covering the same functionality
//I keep this class because of ease or reading the code when it comes to the type of question.
class TrueOrFalseQuestion:public SingleChoiceQuestion
{
    public:
        TrueOrFalseQuestion(custom_string title, custom_string description, bool answer, double points);
};