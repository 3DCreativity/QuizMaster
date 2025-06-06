#include "User.h"
#include "Console.h"
#include "UserType.h"
#include "custom_vector.hpp"
#include <memory>
#include <exception>

void User::login()
{
}

void User::setCommandList() {

}

User& User::currentUser()
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

User::User(): role(UserType::Unknown),name("Undefined"),id(-1),password("") {
	setCommandList();
}

User::User(size_t id, UserType role, custom_string name, custom_string password) : role(role),name(name),id(id) {
	setCommandList();
	//Check password with regex
}


UserType User::getRole()
{
	return this->role;
}

size_t User::getID()
{
	return this->id;
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
	switch (this->command_list.findFirstMatch(input))
	{
	case 0:
		help();
		break;
	case 1:
		login();
		break;
	case 2:
		logout();
		break;
	default:
		Console::displayMessage("Invalid command: \'" + input + "\'\n");
		break;
	}
}

void User::help()
{

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
custom_string User::exportUser()
{
	custom_string result;
	custom_string id_text;
	size_t id_copy = this->id;
	while (id_copy != 0)
	{
		id_text += (char)('0' + id_copy % 10);
		id_copy /= 10;
	}
	result += id_text + " ";
	result += (char)('0' + (int)role) + " ";
	result += name + " " + password + "\n";
	return result;
}

void User::logout()
{
	if (User::instance->getRole() == UserType::Unknown)
	{
		throw new std::exception();
	}
	User::instance = nullptr;
}
