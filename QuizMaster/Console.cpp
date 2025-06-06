#include "Console.h"

#include <iostream>
#include "UserType.h"
#include "User.h"

//void Console::displayConsoleError(custom_string message)
//{
//	cout << "The System has encountered a critical error and cannot run.\nWe are sorry for the caused inconvenience.\nFor emergency cases - call administration at phone: 1234567890\n";
//	FileManager::writeErrorLog(message);
//	
//}

void Console::freeBuffer()
{
	while (buffer.getSize() > 0)
	{
		buffer.remove(buffer.getSize()-1);
	}
}

custom_string Console::prompt(custom_string message)
{
	custom_string input;
	std::cout << message;
	if (buffer.getSize() == 0) {
		std::cin >> input;
		buffer = input.split(' ');
	}
	input = buffer[0];
	buffer.remove(0);
	return input;
}

void Console::displayMessage(custom_string message)
{
	std::cout << message << std::endl;
}

void Console::update()
{
	switch (User::currentUser().getRole())
	{
		case UserType::Unknown:
			std::cout << ":";
			break;
		case UserType::Admin:
			std::cout << "$";
			break;
		case UserType::Player:
			std::cout << ">";
			break;
		default:
			//Console::displayConsoleError(("Current User has no defined User Type.\nReturned value: " + User::currentUser().getType() + "\n"));
			//throw custom exception
			std::cout << "";
			break;
	}
	std::cin >> input;
	buffer = input.split(' ');
	User::currentUser().command(buffer[0]);
	freeBuffer();
	input = "";
}

void Console::displayError(custom_string message)
{
	//TODO: Check if the active user is an admin
	//TODO: Admin case - display error outright
	//TODO: Anyone else case - display that an error occurred but don't specify
	//TODO: Store error for developer handling
}

size_t Console::getBufferSize()
{
	return buffer.getSize();
}
