#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  

#include <memory>
#include <cassert>
#include <iostream>
using std::cout;
using std::cin;

#include "SharedPtr.h"

struct C 
{
	float value;
	C(float value) :value(value) {};
};


void TestG() {
	//-	Konstruktor som tar:	
	//	o	inget	G
	//	o	En SharedPtr	G
	//	o	En pekare	G


	SharedPtr<C> sp11;
	assert(!sp11);
	SharedPtr<C> p15(nullptr);
	assert(!p15);
	SharedPtr<C> sp12(new C(12));
	assert(sp12);
	SharedPtr<C> sp13(sp11);
	assert(!sp13);

	assert(sp12.Unique());
	SharedPtr<C> sp14(sp12);
	assert(sp14);
	assert(!sp12.Unique());


	//-	Destruktor	G
	//It will test itself
	//-	Tilldelning från en	
	//	o	En SharedPtr	G
	sp14 = sp12;
	assert(sp14);

	sp14 = sp14;
	assert(sp14);

	//-	Jämförelse med (== och <)
	SharedPtr<C> sp31(new C(31));
	//	o	En SharedPtr	G
	assert(sp11 == nullptr);
	assert(sp11 < sp12);
	assert(!(sp12 < sp11));
	assert(sp14 == sp12);
	assert(!(sp14 == sp31));
	assert((sp14 < sp31) || (sp31 < sp14));

	//get, * och ->

	SharedPtr<C> sp41(new C(41));
	SharedPtr<C> sp42(new C(42));
	assert((sp41->value) == (sp41.Get()->value));
	assert((sp41->value) != (sp42.Get()->value));
	assert(&(*sp41) == (sp41.Get()));

	//move
	SharedPtr<C> sp51(std::move(sp41));
	assert(sp51->value == 41);
	assert(!sp41);
	sp51.Reset();
	assert(!sp51);
}


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	std::locale::global(std::locale("swedish"));

	TestG();

	std::cin.get();
}

