#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <cassert>
#include "String.h"
#include "StringTest.h"

using std::cout;
using std::cin;

void PrintReallocationScheme() {

	//typedef std::vector<int> Vector;
	//typedef std::string Vector;
	typedef String Vector;
	size_t sz;

	Vector foo;
	sz = foo.capacity();
	std::cout << "mGrowing from default:\n";
	std::cout << "capacity is: " << sz << '\n';
	for (int i = 0; i < 100; ++i) {
		foo.push_back(i);
		if (sz != foo.capacity()) {
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}

	Vector bar;
	bar.reserve(100);   // this is the only difference with foo above
	sz = bar.capacity();
	std::cout << "reserve(100) no reallocations\n";
	std::cout << "capacity is: " << sz << '\n';
	for (int i = 0; i < 100; ++i) {
		bar.push_back(i);
		if (sz != bar.capacity()) {
			sz = bar.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
	std::cin.get();
}

void TestPushBackReallocation() {
	String str("hej");
	assert(str.size() <= str.capacity());

	auto internalBuf = str.data();
	auto cap = str.capacity();
	auto siz = str.size();
	int i;
	for (i = siz + 1; i <= cap; ++i) {
		str.push_back(char(i) + 'a');
		assert(internalBuf == str.data());
		assert(cap == str.capacity());
		assert(i == str.size());
	}
	str.push_back(char(i));
	assert(internalBuf != str.data());
	assert(cap < str.capacity());
	assert(i == str.size());

	assert(str.size() != str.capacity());
	internalBuf = str.data();
	cap = str.capacity();
	siz = str.size();
	str.shrink_to_fit();
	assert(internalBuf != str.data());
	assert(str.size() == str.capacity());
	assert(i == str.size());

	str = "hej";
	str.resize(10);
	assert(10 == str.size() && str[7] == char());
	cap = str.capacity() + 10;
	str.resize(cap);
	assert(str.size() == cap && str.capacity() >= cap);
}

void TestFörGodkäntString() {
	//-	String()
	String str0;
	String str00("");

	assert(str0 == str00);
	str0 != str00;
	//-	String(Sträng sträng)
	String s1("foo"); assert(s1 == "foo");
	String str(s1); assert(str == "foo");
	String s3("bar");  assert(s3 == "bar");

	//-	~String() Kom ihåg destruktorn!
	delete new String("hej");

	//	-	operator =(Sträng sträng)
	assert((str = s3) == s3);
	assert((str = str) == s3);	//self assignment


	String str1("foo"), str2("bar"), str3("hej");
	str3 = str = str1;
	assert(str3 == str);
	assert(str1 == str);

	// operator bool

	assert(String("huj"));
	assert(!String(""));

	//-	operator== 
	//testas överallt!


	//-	operator[](int i) som indexerar utan range check.
	str = "bar";
	str[-1]; str[1000];	//No error
	assert(str[1] == 'a');
	str[1] = 'y';
	assert(str[1] == 'y');

	const String sc(str);
	assert(sc[1] == 'y');
	assert(std::is_const<std::remove_reference< decltype(sc[1])>::type>::value); //Kolla att det blir en const resultat av indexering
																				 //-	push_back(char c) lägger till ett tecken sist.
	str = "bar";
	str.push_back('a');
	assert(str == "bara");
	str.push_back('\0');
	str.push_back('x');
	assert(str.size() == 6 && str[4] == '\0' && str[5] == 'x');

	//-	size(), capacity() and reloccation test;
	TestPushBackReallocation();
	PrintReallocationScheme();

	cout << String("hej\n");
	cout << "Om det står hej på föregående rad så är TestFörGodkänt klar\n";
}