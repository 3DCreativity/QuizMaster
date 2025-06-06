#pragma once

#include <iostream>
#include "custom_vector.hpp"

using namespace std;

class custom_string {
	private:
		char* arr = nullptr;

		void freeDynamic();
		void copyFrom(const custom_string& other);

public:
	custom_string();
	custom_string(char c);
	custom_string(int num);
	custom_string(const char* prov_string);
	custom_string(const custom_string& other);
	custom_string& operator=(const custom_string& other);
	~custom_string();

	const char* c_str() const;
	size_t len() const;
	custom_vector<custom_string> split(const char delimiter);
	bool find(const custom_string& other);

	int toInt();
	double toDouble();
	bool toBool();

	char& operator[](size_t index);
	char operator[](size_t index) const;

	custom_string& operator+=(const custom_string& other);

	friend custom_string operator+(const custom_string& lhs, const custom_string& rhs);
	friend istream& operator>>(istream& in, custom_string& str);

};

ostream& operator<<(ostream& out, const custom_string& str);
bool operator<(const custom_string& lhs, const custom_string& rhs);
bool operator>(const custom_string& lhs, const custom_string& rhs);
bool operator<=(const custom_string& lhs, const custom_string& rhs);
bool operator>=(const custom_string& lhs, const custom_string& rhs);
bool operator==(const custom_string& lhs, const custom_string& rhs);
bool operator!=(const custom_string& lhs, const custom_string& rhs);
