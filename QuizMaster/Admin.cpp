#include "Admin.h"
#include "UserType.h"
#include "Console.h"

void Admin::setCommandList()
{
	this->command_list.add("help", &User::help);
	this->command_list.add("whoami", &User::displayUserInfo);
	this->command_list.add("edit-user", &Admin::edit_user);
	this->admin_command_list.add("pending", &Admin::pending);
	this->admin_command_list.add("approve-quiz", &Admin::approve_quiz);
	this->admin_command_list.add("reject-quiz", &Admin::reject_quiz);
	this->admin_command_list.add("view-reports", &Admin::view_reports);
	this->admin_command_list.add("remove-quiz", &Admin::remove_quiz);
	this->admin_command_list.add("ban", &Admin::ban);
}

Admin::Admin(custom_string username, custom_string name, custom_string password) : User(username, UserType::Admin, name, password) {}

void Admin::exportUser(FileManager manager)
{

}

bool Admin::dispatcher(custom_string input)
{
	try {
		(this->*this->admin_command_list.getValue(input))();
		return true;
	}
	catch (std::invalid_argument) {
		return false;
	}
}

void Admin::pending()
{

}

void Admin::approve_quiz()
{

}

void Admin::reject_quiz()
{
	custom_string id = Console::prompt("Enter the id of the Quiz you wish to reject: ");
	custom_string reason = Console::prompt_ignore_buffer("Please enter a detailed reasoning behind your Quiz rejection: ");
	//FileManager removes the file and writes to the author
	Console::displayMessage("Rejected Quiz #" + id + "\nReason for rejection: " + reason + "\n(Not really)\n");
}

void Admin::view_reports()
{
	//FileManager reads the file
	Console::displayMessage("No reports available\n");
}

void Admin::remove_quiz()
{
	custom_string id = Console::prompt("Enter the id of the Quiz you wish to remove: ");
	//FileManager removes the file
	Console::displayMessage("Removed Quiz #" + id + "\n(Not really)\n");
}

void Admin::ban()
{
	custom_string id = Console::prompt("Enter the username of the user you wish to ban: ");
	//FileManager removes a user
	Console::displayMessage("Banned the user " + id + "\n(Not really)\n");
}
