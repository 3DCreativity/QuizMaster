#pragma once

#include "UserType.h"
#include "custom_hashmap.hpp"
#include "custom_string.h"
#include <memory>

class User
{
private:
	static User* instance;
	UserType role;
	size_t id;
	custom_string name;
	custom_string password;
	void login();
protected:
	custom_vector<custom_string> command_list;
	virtual void setCommandList();
public:
	static User& currentUser();
	static bool isUserDefined();
	User();
	User(size_t id, UserType role, custom_string name, custom_string password);
	User(custom_string template_text);
	virtual ~User() = default;
	UserType getRole();
	size_t getID();
	custom_string getName();
	virtual void command(custom_string input);
	virtual void help();
	void change_password();
	virtual custom_string exportUser();
	void logout();
};