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
	virtual void setCommandList();
	void edit_user();
	void logout();
public:
	static User& getInstance();
	static bool isUserDefined();
	User();
	User(custom_string username, UserType role, custom_string name, custom_string password);
	User(custom_string template_text);
	virtual ~User() = default;
	UserType getRole();
	custom_string getUsername();
	custom_string getName();
	virtual void command(custom_string input);
	virtual void help();
	virtual void exportUser(FileManager manager);
	void quit();
	// virtual custom_string exportUser();
};/* code */