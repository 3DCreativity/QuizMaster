#include "Admin.h"
#include "UserType.h"
#include "Console.h"

void Admin::setCommandList()
{
	this->command_list.add("help", &User::help);
	this->command_help_list.add("help",custom_string() + "help\t\t->\tDisplays all information on available commands");
	this->command_list.add("whoami", &User::displayUserInfo);
	this->command_help_list.add("whoami",custom_string() + "whoami\t\t->\tDisplays the information about the current logged in user");
	this->command_list.add("edit-user", &Admin::edit_user);
	this->command_help_list.add("edit-user",custom_string() + "edit-user\t\t->\tEdits the user data of the currently loggeed in user");
	this->admin_command_list.add("pending", &Admin::pending);
	this->command_help_list.add("pending",custom_string() + "pending\t\t->\tDisplays the pending approval Quizzes");
	this->admin_command_list.add("approve-quiz", &Admin::approve_quiz);
	this->command_help_list.add("approve-quiz",custom_string() + "approve-quiz\t\t->\tApproves a Quiz");
	this->admin_command_list.add("reject-quiz", &Admin::reject_quiz);
	this->command_help_list.add("reject-quiz",custom_string() + "reject-quiz\t\t->\tRejects a Quiz");
	this->admin_command_list.add("view-reports", &Admin::view_reports);
	this->command_help_list.add("view-reports",custom_string() + "view-reports\t\t->\tDisplays all reports by Users");
	this->admin_command_list.add("remove-quiz", &Admin::remove_quiz);
	this->command_help_list.add("remove-quiz",custom_string() + "remove-quiz\t\t->\tRemoves a Quiz");
	this->admin_command_list.add("ban", &Admin::ban);
	this->command_help_list.add("ban",custom_string() + "ban\t\t->\tBans a User from using the system");
}

Admin::Admin(custom_string username, custom_string name, custom_string password) : User(username, UserType::Admin, name, password) {}

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
	Console::displayMessage("This feature is unavailable at the moment");
}

void Admin::approve_quiz()
{
	Console::displayMessage("This feature is unavailable at the moment");
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
