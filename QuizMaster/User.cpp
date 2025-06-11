#include "User.h"
#include "Console.h"
#include "UserType.h"
#include "custom_vector.hpp"
#include "NormalExit.hpp"
#include <memory>
#include <exception>

User* User::instance = nullptr;

void User::change_username()
{
	custom_string username_confirm = Console::prompt_ignore_buffer("Enter your current username: ");
	if (username != username_confirm)
	{
		Console::displayMessage("\nCurrent username mismatch\nNo changes have been made\n");
		return;
	}
	custom_string username_new = Console::prompt_ignore_buffer("Enter your new username: ");

	//TODO: Add regex
	if (username_new.find(' '))
	{
		Console::displayMessage("\nThe provided username is invalid\nNo changes have been made\n");
		return;
	}

	username_confirm = Console::prompt_ignore_buffer("Confirm new username: ");

	if(username_new != username_confirm)
	{
		Console::displayMessage("\nUsername confirmation failed\nNo changes have been made\n");
		return;
	}

	username = username_new;
	Console::displayMessage("\nUsername changed successfully!\n");
}

void User::change_password()
{
	custom_string password_confirm = Console::prompt_ignore_buffer("Enter your current password: ");

	//TODO: Password check must happen with kept encryption. Encrypt the provided password first, then comapare
	if (password_confirm != password)
	{
		Console::displayMessage("\nCurrent password mismatch\nPassword was not changed\n");
		return;
	}
	custom_string password_new = Console::prompt_ignore_buffer("Enter your new password: ");
	//Checks the password with regex
	//If it doesn't meet the requirement - good placed message and a return
	//Temporary critical check - to be replaced later with regex
	/*if (password_new.find(' '))
	{
		Console::displayMessage("Invalid password syntax - no spaces are allowed");
		return;
	}*/
	password_confirm = Console::prompt_ignore_buffer("Confirm your new password: ");
	if (password_confirm != password_new)
	{
		Console::displayMessage("\nPassword mismatch\nPassword was not changed\n");
		return;
	}

	//TODO: Encrypt password before setting it
	password = password_new;
	Console::displayMessage("\nPassword changed successfully\n");
}

void User::change_name()
{
	custom_string first_name = Console::prompt_ignore_buffer("Enter first name: ");
	custom_string middle_name = Console::prompt_ignore_buffer("Enter middle name: ");
	custom_string last_name = Console::prompt_ignore_buffer("Enter last name: ");
	if (Console::prompt_ignore_buffer("Is " + first_name + " " + middle_name + " " + last_name + " your full name?(y/n): ") == 'y')
	{
		name = first_name + " " + middle_name + " " + last_name;
		Console::displayMessage("\nName changed successfully!\n");
	}
	else
	{
		Console::displayMessage("\nName changing aborted\nNo changes have been made\n");
	}
}

void User::login()
{

}

void User::setCommandList() {
	this->command_list.add("help",&User::help);
	this->command_list.add("quit",&User::quit);
	this->command_list.add("whoami", &User::displayUserInfo);
	this->command_list.add("edit_user", &User::edit_user);
}

void User::edit_user()
{
	bool runEditUser = true;
	while (runEditUser)
	{
		Console::displayMessage("User change menu:\n\nWhat would you like to do?\n");
		custom_string answer = Console::prompt_ignore_buffer("1.) Change Username\n2.) Change Password\n3.) Change Name\n4.) Quit User change menu\n\n");
		switch (answer.toInt())
		{
		case 1:
			change_username();
			break;
		case 2:
			change_password();
			break;
		case 3:
			change_name();
			break;
		case 4:
			runEditUser = false;
			break;
		default:
			Console::displayMessage("Invalid agrument was passed\n");
			break;
		}
	}
}

void User::logout()
{
	if (User::instance->getRole() == UserType::Unknown)
	{
		throw new std::exception();
	}
	User::instance = nullptr;
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
		if (!dispatcher(input)) {
			Console::displayMessage("Invalid command\nFor more info on available commands, please use command\nhelp");
		}
	}
}

void User::help()
{
	Console::displayMessage("No commands are currently available\nSorry ;)");
}

void User::displayUserInfo()
{
	bool passReveal = (Console::prompt("Do you wish to reveal your password?(y/n): ") == 'y');
	Console::displayMessage(custom_string() + "User info:\n\n" +
							"Name\n" + this->name + "\n\n" +
							"Username\n" + this->username + "\n\n" +
							"Password\n" + (passReveal?this->password:"*****") + "\n\n" +
							"User Type");
	switch (this->role)
	{
		case UserType::Unknown:
			Console::displayMessage("Undefined");
			break;
		case UserType::Admin:
			Console::displayMessage("Administrator");
			break;
		case UserType::Player:
			Console::displayMessage("Player");
			break;
		default:
			Console::displayMessage("<Error retrieving UserType>");
			break;
	}
}

void User::exportUser(FileManager manager)
{
	//Do nothing
}

void User::quit()
{
	//saveState();
	throw NormalExit("Quitting program...");
}

bool User::dispatcher(custom_string input)
{
	return false;
}