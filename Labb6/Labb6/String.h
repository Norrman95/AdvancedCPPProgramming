#pragma once
#include <iostream>
#include <memory.h>
#include "StringItt.h"

class String
{
	char* cString;
	int currCapacity;
	int currContent;
public:
	typedef StringItt<char>::iterator iterator;
	typedef StringItt<char>::reverse_iterator reverse_iterator;

	iterator begin()
	{
		return iterator(cString);
	}
	iterator end()
	{
		return iterator(cString + currContent);
	}
	reverse_iterator rbegin()
	{
		return reverse_iterator(&cString[currContent - 1]);
	}
	reverse_iterator rend()
	{
		return reverse_iterator(cString - 1);
	}
#pragma region gammalt
	~String()
	{
		cString = nullptr;
	}
	String(const char* cstr);
	friend bool operator==(const String& lhs, const String& rhs);
	friend std::ostream& operator<<(std::ostream& cout, String& rhs)
	{
		for (size_t i = 0; i < rhs.currContent; ++i)
		{
			cout << rhs.cString[i];
		}
		return cout;
	}
#pragma endregion
};