#include "Admin.h"
#include "UserType.h"

void Admin::setCommandList()
{
	this->command_list.add("help", &User::help);
	this->command_list.add("whoami", &User::displayUserInfo);
	this->command_list.add("edit-user", &User::edit_user);
	this->admin_command_list.add("pending", &Admin::pending);
	this->admin_command_list.add("approve-quiz", &Admin::approve_quiz);
	this->admin_command_list.add("reject-quiz", &Admin::reject_quiz);
	this->admin_command_list.add("view-reports", &Admin::view_reports);
	this->admin_command_list.add("remove-quiz", &Admin::remove_quiz);
	this->admin_command_list.add("ban", &Admin::ban);
}

Admin::Admin(custom_string username, custom_string name, custom_string password) : User(username, UserType::Admin, name, password) {}


void Admin::help() 
{

}

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

}

void Admin::view_reports()
{

}

void Admin::remove_quiz()
{

}

void Admin::ban()
{

}
