#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include "String.h"
#include "memory.h"
#include <iostream>
#include <utility>  
#include <cassert>
#include <algorithm>

using namespace std;

String::String()
{
	currContent = 0;
	currCapacity = 0;
	cString = new char[0];
}
String::~String()
{
	delete[] cString;
	cString = nullptr;
}
String::String(const String& rhs)
{
	currContent = rhs.currContent;
	currCapacity = rhs.currCapacity;

	cString = new char[currCapacity + 1];
	for (size_t i = 0; i < currContent + 1; i++)
	{
		cString[i] = rhs.cString[i];
	}
	cString[currContent] = '\0';

	assert(Invariant());
}
String::String(const char* cstr)
{
	currContent = strlen(cstr);
	currCapacity = strlen(cstr);

	cString = new char[currCapacity + 1];
	for (size_t i = 0; i < currContent + 1; i++)
	{
		cString[i] = cstr[i];
	}
	cString[currContent] = '\0';

	assert(Invariant());
}
String::operator bool()
{
	return (currContent > 0);
}
int String::capacity() const
{
	return currCapacity;
}
int String::size() const
{
	return currContent;
}
const char * String::data() const
{
	return cString;
}
char& String::operator[](int i)
{
	return cString[i];
}
const char& String::operator[](int i) const
{
	return cString[i];
}
String & String::operator=(const String & rhs)
{
	assert(Invariant());

	if (size() < rhs.size())
	{
		char* temp = new char[rhs.size()];
		for (size_t i = 0; i < rhs.size(); i++)
		{
			temp[i] = rhs.cString[i];
		}

		delete[] cString;
		cString = temp;
		cString[currContent] = '\0';
	}
	else
	{
		for (size_t i = 0; i < rhs.size(); i++)
		{
			cString[i] = rhs.cString[i];
		}
	}

	assert(Invariant());
	return *this;
}
String & String::operator+=(const String & rhs)
{
	return *this;
}
String String::operator+()
{
	return String();
}
void String::reserve(size_t n)
{
	assert(Invariant());

	delete[] cString;
	cString = new char[n];
	currContent = 0;
	currCapacity = n;

	assert(Invariant());
}
char & String::at(size_t n)
{
	try
	{
		if (n > currContent)
		{
			throw;
		}
		else
		{
			return cString[n];
		}
	}
	catch (const std::exception& e)
	{
		cout << "out_of_range" << endl;
	}
	return cString[n];
}
void String::shrink_to_fit()
{
	assert(Invariant());

	char* temp = new char[currContent + 1];

	for (size_t i = 0; i < currContent; i++)
	{
		temp[i] = cString[i];
	}
	delete[] cString;
	cString = temp;
	cString[currContent] = '\0';
	currCapacity = currContent;

	assert(Invariant());
}
void String::push_back(char c)
{
	assert(Invariant());

	if (currCapacity == currContent || currCapacity == 0 || currCapacity == (currContent + 1))
	{
		size_t n = max(4, 2 * capacity());
		currCapacity = n;

		char* temp = new char[n + 1];
		for (size_t i = 0; i < currContent + 1; i++)
		{
			temp[i] = cString[i];
		}
		temp[currContent++] = c;
		temp[currContent] = '\0';

		delete[] cString;
		cString = temp;
	}
	else
	{
		cString[currContent++] = c;
		cString[currContent] = '\0';
	}

	assert(Invariant());
}
void String::resize(size_t n)
{
	assert(Invariant());

	char* temp = new char[n + 1];
	for (size_t i = 0; i < n + 1; i++)
	{
		if (currContent > i)
		{
			temp[i] = cString[i];
		}
		else
		{
			temp[i] = char();
		}
	}

	currContent = n;
	currCapacity = n;

	delete[] cString;
	cString = temp;
	cString[currContent] = '\0';

	assert(Invariant());
}
bool operator==(const String & lhs, const String & rhs)
{
	if (lhs.size() == rhs.size())
	{
		for (size_t i = 0; i < lhs.size(); i++)
		{
			if (lhs.cString[i] != rhs.cString[i])
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}
bool operator!=(const String & lhs, const String & rhs)
{
	if (lhs.size() == rhs.size())
	{
		for (size_t i = 0; i < lhs.size(); i++)
		{
			if (lhs.cString[i] != rhs.cString[i])
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		return true;
	}
}