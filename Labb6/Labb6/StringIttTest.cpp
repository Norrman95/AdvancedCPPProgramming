#include "String.h"
#include "StringItt.h"
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;

void TestIttPart() 
{
	String s1("foobar");
	for (auto i = s1.begin(); i != s1.end(); i++)
		cout << *i;
	cout << endl;
	//s1 = "raboof";
	auto it = s1.begin();
	assert(*it == 'f');
	assert(*(it++) == 'f' && *it == 'o');
	++it;
	assert(*++it == 'b');
	assert(*(it + 1) == 'a');
	assert(it[2] == 'r');
}

void TestIttPartR() 
{
	String s1("foobar");
	for (auto i = s1.rbegin(); i != s1.rend(); i++)
		cout << *i;
	cout << endl;
	s1 = "raboof";
	auto it = s1.rbegin();
	assert(*it == 'f');

	assert(*(it++) == 'f' && *it == 'o');
	++it;
	assert(*++it == 'b');
	assert(*(it + 1) == 'a');
	assert(it[2] == 'r');
}

void TestFörGodkäntItt() 
{

	String::iterator Str;
	String::reverse_iterator rStr;

	TestIttPart();
	TestIttPartR();

	String s("foobar");
	Str = s.begin();
	rStr = s.rbegin();


	*Str = 'a';
	*(rStr + 2) = 'c';
	assert(s == "aoocar");

	cout << "\nTestFörGodkänt Itt klar\n";
}