#include "custom_string.h"
#include <string.h>

void custom_string::freeDynamic()
{
	delete[] arr;
	arr = nullptr;
}

void custom_string::copyFrom(const custom_string& other)
{
	if (arr != nullptr)
	{
		freeDynamic();
	}
	size_t length = strlen(other.arr);
	arr = new char[length + 1];
	strncpy(arr,other.arr,length+1); // -> Linux
	// strcpy_s(arr, length + 1, other.arr); //-> Windows
}

custom_string::custom_string()
{
	arr = new char[1];
	arr[0] = '\0';
}

custom_string::custom_string(char c)
{
	arr = new char[2];
	arr[0] = c;
	arr[1] = '\0';
}

custom_string::custom_string(int num)
{
	bool negative = num < 0;
	size_t size = 0;
	int temp = num;
	while (temp != 0)
	{
		temp /= 10;
		size++;
	}
	temp = num;
	arr = new char[size + 1 + (int)negative];
	if (negative)
	{
		temp *= -1;
		arr[0] = '-';
	}
	for (size_t i = negative; i < size; i++)
	{
		arr[i] = '0' + temp % 10;
		temp /= 10;
	}
	arr[size] = '\0';
}

custom_string::custom_string(const char* prov_string)
{
	if (prov_string == nullptr)
	{		
		arr = new char[1];
		arr[0] = '\0';
	}
	else
	{
		size_t length = strlen(prov_string);
		arr = new char[length + 1];
		strncpy(arr,prov_string,length+1); // -> Linux
		// strcpy_s(arr, length + 1, prov_string); // -> Windows
	}
}

custom_string::custom_string(const custom_string& other)
{
	copyFrom(other);
}

custom_string& custom_string::operator=(const custom_string& other)
{
	if (this != &other)
	{
		freeDynamic();
		copyFrom(other);
	}

	return *this;
}

custom_string::~custom_string()
{
	freeDynamic();
}

const char* custom_string::c_str() const
{
	return arr;
}

size_t custom_string::len() const
{
	return strlen(arr);
}

custom_vector<custom_string> custom_string::split(const char delimiter = ' ')
{
	custom_vector<custom_string> result;
	custom_string current_str;
	char current_char;

	for (size_t i = 0; i < len(); i++)
	{
		current_char = arr[i];
		if (current_char == delimiter && current_str.len() > 0)
		{
			result.add(current_str);
			current_str = "";
		}
		else
		{
			current_str += current_char;
		}
	}
	result.add(current_str);
	return result;
}

bool custom_string::find(const custom_string& other)
{
	size_t index_origin = 0;
	size_t index_other = 0;
	bool comparison;

	while (
		index_origin < this->len() && 
		index_other < other.len() &&
		(index_origin + index_other) < this->len()
		)
	{
		comparison = this->arr[index_origin + index_other] == other.arr[index_other];
		if (!comparison)
		{
			index_origin++;
		}
		else {
			index_other++;
		}
	}

	return index_other == other.len();
}

int custom_string::toInt()
{
	int result = 0;
	size_t index = 0;
	while (index != this->len() && !(this->arr[index] >= '0' && this->arr[index] <= '9'))
	{
		result *= 10;
		result += '9' - this->arr[index];
		index++;
	}
	return result;
}

double custom_string::toDouble()
{
	double whole_num = 0;
	double remainder = 0;
	size_t remainder_len = 1;
	size_t index = 0;
	while (index != this->len() && !(this->arr[index] >= '0' && this->arr[index] <= '9'))
	{
		whole_num *= 10;
		whole_num += '9' - this->arr[index];
		index++;
	}
	if (this->arr[index] == '.' || this->arr[index] == ',')
	{
		index++;
	}
	while (index != this->len() && !(this->arr[index] >= '0' && this->arr[index] <= '9'))
	{
		remainder *= 10;
		remainder += '9' - this->arr[index];
		index++;
		remainder_len*=10;
	}
	remainder = remainder / remainder_len;
	whole_num += remainder;
	return whole_num;
}

bool custom_string::toBool()
{
	if (this->arr[0] == '1')
	{
		return true;
	}
	if (this->arr[0] == '0')
	{
		return false;
	}
	if (*this == "true" || *this == "TRUE")
	{
		return true;
	}
	return false;
}


char& custom_string::operator[](size_t index)
{
	return arr[index];
}

char custom_string::operator[](size_t index) const
{
	return arr[index];
}

custom_string& custom_string::operator+=(const custom_string& other)
{
	size_t length = len() + other.len();

	char* arr_mod = new char[length + 1];
	
	arr_mod[0] = '\0';

	strncat(arr_mod,arr,length+1); // -> Linux
	strncat(arr_mod,other.arr,length+1); // -> Linux
	// strcat_s(arr_mod, length + 1, arr); // -> Windows
	// strcat_s(arr_mod, length + 1, other.arr); // -> Windows

	freeDynamic();
	arr = arr_mod;

	return *this;
}

custom_string operator+(const custom_string& lhs, const custom_string& rhs)
{
	custom_string result(lhs);

	result += rhs;

	return result;
}

istream& operator>>(istream& in, custom_string& str)
{
	char buffer[1024];
	in.getline(buffer, 1024);

	size_t buffer_length = strlen(buffer);

	str.freeDynamic();
	str.arr = new char[buffer_length + 1];

	strncpy(str.arr,buffer,buffer_length+1); // -> Linux
	// strcpy_s(str.arr, buffer_length + 1, buffer); // -> Windows

	return in;
}

ostream& operator<<(ostream& out, const custom_string& str)
{
	return out << str.c_str();
}

bool operator<(const custom_string& lhs, const custom_string& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator>(const custom_string& lhs, const custom_string& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator<=(const custom_string& lhs, const custom_string& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>=(const custom_string& lhs, const custom_string& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}

bool operator==(const custom_string& lhs, const custom_string& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const custom_string& lhs, const custom_string& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}

