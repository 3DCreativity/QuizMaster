#pragma once

#include "custom_string.h"
#include "custom_vector.hpp"

class Console
{
private:
	//static void displayConsoleError(custom_string message);
	static custom_string input;
	static custom_vector<custom_string> buffer;
	static void freeBuffer();
public:
	static custom_string prompt(custom_string message);
	static void displayMessage(custom_string message);
	static void update();
	static void displayError(custom_string message);
	static size_t getBufferSize();
	~Console() = default;
};