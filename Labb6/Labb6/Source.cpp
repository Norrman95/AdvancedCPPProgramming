#include "StringIttTest.h"
#include "String.h"
#include <cassert>
#include <iostream>
#include <utility>

using namespace std;

#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
#include "StringItt.h"

int main()
{
	std::locale::global(std::locale("swedish"));
	TestFörGodkäntItt();
	cin.get();

	return 0;
}