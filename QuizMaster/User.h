#pragma once

#include "UserType.h"
#include "FileManager.h"
#include "custom_hashmap.hpp"
#include "custom_string.h"
#include <memory>

class User
{
private:
	static User* instance;
	UserType role;
	custom_string username;
	custom_string name;
	custom_string password;
	void change_username();
	void change_password();
	void change_name();
	void login();
protected:
	/* void ([Class_Name]::*) ([Parameters]) is the syntax for class member function pointers
	This method also uses the vtables the way a normal function call would (experimented)
	Source: https://isocpp.org/wiki/faq/pointers-to-members */
	custom_hashmap<custom_string,void (User::*)()> command_list; 
	custom_hashmap<custom_string,custom_string> command_help_list;
	virtual void setCommandList();
	void edit_user();
	void logout();
public:
	static User& getInstance();
	static bool isUserDefined();
	User();
	User(custom_string username, UserType role, custom_string name, custom_string password);
	virtual ~User() = default;
	UserType getRole();
	custom_string getUsername();
	custom_string getName();
	void command(custom_string input);
	void help();
	void displayUserInfo();
	virtual void exportUser(FileManager manager);
	void quit();
	virtual bool dispatcher(custom_string input); //For Derived classes
};