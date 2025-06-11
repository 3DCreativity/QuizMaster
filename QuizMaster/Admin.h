#pragma once
#include "User.h"
#include "FileManager.h"
#include "custom_string.h"
#include "custom_vector.hpp"
#include "custom_hashmap.hpp"

class Admin : public User {
private:
	custom_hashmap<custom_string, void (Admin::*)()> admin_command_list;
protected:
	void setCommandList() override;
public:
	Admin(custom_string username, custom_string name, custom_string password);
	void help() override;
	void exportUser(FileManager manager) override;
	bool dispatcher(custom_string input) override;
	void pending();
	void approve_quiz();
	void reject_quiz();
	void view_reports();
	void remove_quiz();
	void ban();
};