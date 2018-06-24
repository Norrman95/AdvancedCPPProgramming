#pragma once
#include <iostream>
#include <memory.h>

class String
{
	char* cString;
	int currCapacity;
	int currContent;

public:
	bool Invariant()
	{
		if (cString == nullptr)
		{
			return false;
		}
		if (currContent > currCapacity)
		{
			return false;
		}
		return true;
	}

	~String();
	String();
	String(const String& rhs);
	String(const char* cstr);

	String& operator=(const String& rhs);
	explicit operator bool();

	char& at(size_t i);
	char& operator[](int i);
	const char& operator[](int i) const;
	const char* data() const;

	int size()const;
	void reserve(size_t n);
	int capacity() const;
	void shrink_to_fit();
	void push_back(char c);
	void resize(size_t n);

	String& operator+=(const String& rhs);
	String operator+();
	friend bool operator==(const String& lhs, const String& rhs);
	friend bool operator!=(const String& lhs, const String& rhs);

	friend std::ostream& operator<<(std::ostream& cout, String& rhs) 
	{
		for (size_t i = 0; i < rhs.size(); ++i) 
		{
			cout << rhs.cString[i];
		}
		return cout;
	}
};