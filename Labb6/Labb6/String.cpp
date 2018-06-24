#include "String.h"
#include "memory.h"
#include <iostream>
#include <utility>  
#include <cassert>
#include <algorithm>

using namespace std;

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
}

bool operator==(const String & lhs, const String & rhs)
{
	if (lhs.currContent == rhs.currContent)
	{
		for (size_t i = 0; i < lhs.currContent; i++)
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