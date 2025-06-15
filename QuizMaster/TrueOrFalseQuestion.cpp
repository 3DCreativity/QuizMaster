#include "TrueOrFalseQuestion.h"
#include "custom_string.h"
#include "SingleChoiceQuestion.h"

TrueOrFalseQuestion::TrueOrFalseQuestion(custom_string title, custom_string description, bool answer, double points):SingleChoiceQuestion(title,description,answer,points) {}