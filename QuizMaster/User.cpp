#include "User.h"
#include "Console.h"
#include "UserType.h"
#include "custom_vector.hpp"
#include "NormalExit.hpp"
#include <memory>
#include <exception>

User* User::instance = nullptr;

void User::login()
{
}

void User::setCommandList() {
	this->command_list.add("help",&User::help);
	this->command_list.add("quit",&User::quit);
}

User& User::getInstance()
{
	if (User::instance == nullptr)
	{
		User::instance = new User();
	}
	return *User::instance;
}

bool User::isUserDefined()
{
	if (User::instance == nullptr)
	{
		return false;
	}
	return true;
}

User::User(): role(UserType::Unknown),name("Undefined"),username("unknown"),password("") {
	setCommandList();
}

User::User(custom_string username, UserType role, custom_string name, custom_string password) : role(role),name(name),username(username) {
	setCommandList();
	//Check password with regex
}


UserType User::getRole()
{
	return this->role;
}

custom_string User::getUsername()
{
	return this->username;
}

custom_string User::getName()
{
	return this->name;
}

void User::command(custom_string input)
{	
	if (input.find(' '))
	{
		//Handle an error - unpredicted behaviour
		Console::displayMessage("Invalid command context was passed\nNot a valid command: " + input + "\n");
		return;
	}
	try{
		(this->*this->command_list.getValue(input))();
	}
	catch(std::invalid_argument)
	{
		Console::displayMessage("Invalid command\nFor more info on available commands, please use command\nhelp");
	}
}

void User::help()
{
	Console::displayMessage("No commands are currently available\nSorry ;)");
}

void User::change_password()
{
	custom_string password_confirm = Console::prompt("Enter your current password: ");
	if (password_confirm != password)
	{
		Console::displayMessage("Current password mismatch\nPassword was not changed");
		return;
	}
	custom_string password_new = Console::prompt("Enter your new password: ");
	//Checks the password with regex
	//If it doesn't meet the requirement - good placed message and a return
	//Temporary critical check - to be replaced later with regex
	if (password_new.find(' '))
	{
		Console::displayMessage("Invalid password syntax - no spaces are allowed");
		return;
	}
	password_confirm = Console::prompt("Confirm your new password: ");
	if (password_confirm != password_new)
	{
		Console::displayMessage("Password mismatch\nPassword was not changed");
		return;
	}
	password = password_new;
	Console::displayMessage("Password changed successfully");
}

//Old code - integrate Visitor pattern across the File Manager. Keep passwords safe, even at base level

void User::logout()
{
	if (User::instance->getRole() == UserType::Unknown)
	{
		throw new std::exception();
	}
	User::instance = nullptr;
}

void User::exportUser(FileManager manager)
{
	//Do nothing
}

void User::quit()
{
	throw NormalExit("Quitting program...");
}